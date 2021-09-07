#include "JsonImportPrivatePCH.h"
#include "MeshBuilder.h"
#include "UnrealUtilities.h"
#include "MeshBuilderUtils.h"

#include "Editor/UnrealEd/Private/GeomFitUtils.h"
#include "PhysicsEngine/BodySetup.h"

void MeshBuilder::setupStaticMesh(UStaticMesh *mesh, const JsonMesh &jsonMesh, std::function<void(TArray<FStaticMaterial> &meshMaterial)> materialSetup){
	using namespace UnrealUtilities;
	using namespace MeshBuilderUtils;

	check(mesh);

	UE_LOG(JsonLog, Log, TEXT("Static mesh num lods: %d"), getNumLods(mesh));

	if (getNumLods(mesh) < 1){
		UE_LOG(JsonLog, Warning, TEXT("Adding static mesh lod!"));
		addSourceModel(mesh);
	}
	 
	int32 lod = 0;

	FStaticMeshSourceModel& srcModel = getSourceModel(mesh, lod);

//#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 22)
#ifdef EXODUS_UE_VER_4_22_GE
	srcModel.StaticMeshOwner = mesh;
#endif

	mesh->LightingGuid = FGuid::NewGuid();
	mesh->LightMapResolution = 64;
	mesh->LightMapCoordinateIndex = 1;

	FRawMesh newRawMesh;
	srcModel.RawMeshBulkData->LoadRawMesh(newRawMesh);
	newRawMesh.VertexPositions.SetNum(0);

	UE_LOG(JsonLog, Log, TEXT("Num normal floats: %d"), jsonMesh.verts.Num());
	bool hasNormals = jsonMesh.normals.Num() != 0;
	UE_LOG(JsonLog, Log, TEXT("has normals: %d"), (int)hasNormals);
	bool hasColors = jsonMesh.colors.Num() > 0;
	bool hasTangents = jsonMesh.tangents.Num() != 0;
	UE_LOG(JsonLog, Log, TEXT("hasColors: %d; hasTangents: %d"), (int)hasColors, (int)hasNormals);

	{//why?
		UE_LOG(JsonLog, Log, TEXT("Generating mesh"));
		UE_LOG(JsonLog, Log, TEXT("Num vert floats: %d"), jsonMesh.verts.Num());//vertFloats.Num());
		for(int i = 0; (i + 2) < jsonMesh.verts.Num(); i += 3){
			FVector unityPos(jsonMesh.verts[i], jsonMesh.verts[i+1], jsonMesh.verts[i+2]);
			newRawMesh.VertexPositions.Add(unityPosToUe(unityPos));
		}
		UE_LOG(JsonLog, Log, TEXT("Num verts: %d"), newRawMesh.VertexPositions.Num());

		//const auto &normalFloats = jsonMesh.normals;

		const int32 maxUvs = 8;
		const TArray<float>* uvFloats[maxUvs] = {
			&jsonMesh.uv0, &jsonMesh.uv1, &jsonMesh.uv2, &jsonMesh.uv3, 
			&jsonMesh.uv4, &jsonMesh.uv5, &jsonMesh.uv6, &jsonMesh.uv7
		};

		bool hasUvs[maxUvs];
		for(int32 i = 0; i < maxUvs; i++){
			hasUvs[i] = uvFloats[i]->Num() != 0;
			UE_LOG(JsonLog, Log, TEXT("Uv floats[%d]: %d, hasUvs: %d"), i, uvFloats[i]->Num(), (int)hasUvs[i]);
		}

		if (!hasUvs[0]){
			UE_LOG(JsonLog, Warning, TEXT("No default uvs found on mesh %s(%d). Placeholder coordinates will be used."), *jsonMesh.name, jsonMesh.id.id);
		}

		//submesh generation
		newRawMesh.WedgeIndices.SetNum(0);

		for(int i = 0; i < MAX_MESH_TEXTURE_COORDS; i++)
			newRawMesh.WedgeTexCoords[i].SetNum(0);

		newRawMesh.WedgeColors.SetNum(0);
		newRawMesh.WedgeTangentX.SetNum(0);
		newRawMesh.WedgeTangentY.SetNum(0);
		newRawMesh.WedgeTangentZ.SetNum(0);

		UE_LOG(JsonLog, Log, TEXT("Sub meshes: %d"), jsonMesh.subMeshes.Num());
		if (jsonMesh.subMeshes.Num() > 0){
			UE_LOG(JsonLog, Log, TEXT("Processing submeshes"));
			int32 nextMatIndex = 0;

			for(int subMeshIndex = 0; subMeshIndex < jsonMesh.subMeshes.Num(); subMeshIndex++){
				const auto& curSubMesh = jsonMesh.subMeshes[subMeshIndex];

				const auto& trigs = curSubMesh.triangles;
				UE_LOG(JsonLog, Log, TEXT("Num triangle verts %d"), trigs.Num());

				auto processTriangleIndex = [&](int32 trigVertIdx){
					auto origIndex = trigs[trigVertIdx];
					newRawMesh.WedgeIndices.Add(origIndex);

					processTangent(origIndex, jsonMesh.normals, jsonMesh.tangents, hasNormals, hasTangents, 
						[&](const auto& norm){
							newRawMesh.WedgeTangentZ.Add(norm);
						},
						[&](const auto &tanU, const auto &tanV){
							newRawMesh.WedgeTangentX.Add(tanU);
							newRawMesh.WedgeTangentY.Add(tanV);
						}
					);

					for(int32 uvIndex = 0; uvIndex < maxUvs; uvIndex++){
						if (!hasUvs[uvIndex]){
							if (uvIndex != 0)
								continue;
							auto tmpPos = getIdxVector3(jsonMesh.verts, origIndex);
							FVector2D tmpUv(tmpPos.X, tmpPos.Y);
							newRawMesh.WedgeTexCoords[uvIndex].Add(tmpUv);
							continue;
						}

						auto tmpUv = getIdxVector2(*uvFloats[uvIndex], origIndex);
						tmpUv.Y = 1.0f - tmpUv.Y;
						newRawMesh.WedgeTexCoords[uvIndex].Add(tmpUv);
					}

					if (hasColors){
						FColor col32(
							jsonMesh.colors[origIndex * 4], 
							jsonMesh.colors[origIndex * 4 + 1], 
							jsonMesh.colors[origIndex * 4 + 2], 
							jsonMesh.colors[origIndex * 4 + 3]
						);

						//srgb conversion, though?
						newRawMesh.WedgeColors.Add(
							col32
						);
					}

					if ((trigVertIdx % 3) == 0){
						newRawMesh.FaceMaterialIndices.Add(subMeshIndex);
						newRawMesh.FaceSmoothingMasks.Add(0);
					}
				};

				for(int32 trigVertIndex = 0; (trigVertIndex + 2) < trigs.Num(); trigVertIndex += 3){
					processTriangleIndex(trigVertIndex);
					processTriangleIndex(trigVertIndex + 2);
					processTriangleIndex(trigVertIndex + 1);
				}

				UE_LOG(JsonLog, Log, TEXT("New wedge indices %d"), newRawMesh.WedgeIndices.Num());
				UE_LOG(JsonLog, Log, TEXT("Face mat indices: %d"), newRawMesh.FaceMaterialIndices.Num());
				for(int32 i = 0; i < MAX_MESH_TEXTURE_COORDS; i++){
					UE_LOG(JsonLog, Log, TEXT("Uv[%d] size: %d"), i, newRawMesh.WedgeTexCoords[i].Num());
				}
			}
		}
		else{
			UE_LOG(JsonLog, Warning, TEXT("No Submeshes found!"));
		}
	}

	bool valid = newRawMesh.IsValid();
	bool fixable = newRawMesh.IsValidOrFixable();
	UE_LOG(JsonLog, Log, TEXT("Mesh is valid: %d, mesh is validOrFixable: %d"), (int)valid, (int)fixable);
	if (!valid){
		UE_LOG(JsonLog, Warning, TEXT("Mesh is not valid!"));
		if (!fixable){
			UE_LOG(JsonLog, Warning, TEXT("Mesh is not fixable!"));
		}
	}

	if (materialSetup){
		materialSetup(mesh->StaticMaterials);
	}

	srcModel.RawMeshBulkData->SaveRawMesh(newRawMesh);

	srcModel.BuildSettings.bRecomputeNormals = false;//!hasNormals; //Why??
	srcModel.BuildSettings.bRecomputeTangents = !(hasTangents && hasNormals);//true;

	TArray<FText> buildErrors;
	mesh->Build(false, &buildErrors);
	if (buildErrors.Num() > 0){
		FString errMsg;
		for (FText& err : buildErrors){
			errMsg += FString::Printf(TEXT("MeshBuildError: %s"), *(err.ToString()));
			//UE_LOG(JsonLog, Error, TEXT("MeshBuildError: %s"), *(err.ToString()));
		}
		UE_LOG(JsonLog, Warning, TEXT("Build errors while loading mesh %d(\"%s\"):\n%s"), (int)jsonMesh.id, *jsonMesh.name, *errMsg);
	}
	else{
		TArray<FVector> verts(KDopDir18, 18);
		GenerateKDopAsSimpleCollision(mesh, verts);

		UBodySetup* bodySetup = mesh->BodySetup;
		if (!bodySetup || (bodySetup && (bodySetup->AggGeom.GetElementCount() == 0))){
			UE_LOG(JsonLog, Warning, TEXT("Could not generate convex collision for mesh %d(\"%s\"):\nRebuilding as a box."), (int)jsonMesh.id, *jsonMesh.name);
			GenerateBoxAsSimpleCollision(mesh);
		}

		if (bodySetup){
			/*
			This is used by imported mesh colliders. 
			Unity engine allows toggling of collision mesh being/not being convex on the fly, and does not 
			generate simple collision by default.

			SO if either "convex" or "triangle" flags are set, the importer will adjust collision strategy to mimic unity's.

			Convex will use KDop approach and make the mesh use "simple as complex", while triangular will use 
			triangular geometry AND mark mesh as "use complex as simple".

			If neither is set, it will use default strategy.

			...

			I wish there was a separation between mesh and collider, though.
			*/
			if (jsonMesh.convexCollider){
				bodySetup->CollisionTraceFlag = CTF_UseSimpleAsComplex;
			}
			else if (jsonMesh.triangleCollider){
				bodySetup->CollisionTraceFlag = CTF_UseComplexAsSimple;
			}
		}
		if (!bodySetup && (jsonMesh.convexCollider || jsonMesh.triangleCollider)){
			UE_LOG(JsonLog, Warning, TEXT("Could not setup collision flags for mesh %d(\"%s\") - body setup not generated"), (int)jsonMesh.id, *jsonMesh.name);
		}
	}

//#if (ENGINE_MAJOR_VERSION >= 4) && (ENGINE_MINOR_VERSION >= 22)
#ifdef EXODUS_UE_VER_4_22_GE
	srcModel.StaticMeshOwner = mesh;
#endif
}
