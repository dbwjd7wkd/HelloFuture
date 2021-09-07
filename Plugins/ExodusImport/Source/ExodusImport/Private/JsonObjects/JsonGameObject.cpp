#include "JsonImportPrivatePCH.h"
#include "JsonGameObject.h"
#include "macros.h"
#include "UnrealUtilities.h"

/*
Apparently Unreal 4 build system concatenates all the cpp files together during compilation phase.
Meaning... *.cpp units are not isolated from each other.

Apparently Intellisense is unaware of that.

I guess it means I should no longer place "using namespace" at beginning of *.cpp files and expect it to be isolated.
*/

JsonGameObject::JsonGameObject(JsonObjPtr jsonData){
	load(jsonData);
}

void JsonGameObject::load(JsonObjPtr jsonData){
	using namespace JsonObjects;
	using namespace UnrealUtilities;

	JSON_GET_PARAM(jsonData, name, getString);
	JSON_GET_PARAM(jsonData, id, getInt);

	JSON_GET_PARAM(jsonData, scenePath, getString);

	JSON_GET_PARAM(jsonData, instanceId, getInt);
	JSON_GET_PARAM(jsonData, localPosition, getVector);
	JSON_GET_PARAM(jsonData, localRotation, getQuat);
	JSON_GET_PARAM(jsonData, localScale, getVector);
	JSON_GET_PARAM(jsonData, worldMatrix, getMatrix);
	JSON_GET_PARAM(jsonData, localMatrix, getMatrix);
	JSON_GET_PARAM2(jsonData, parentId, parent, getInt);

	JSON_GET_PARAM2(jsonData, parentName, parentName, getString);

	JSON_GET_PARAM2(jsonData, meshId, mesh, getResId);

	JSON_GET_PARAM(jsonData, activeSelf, getBool);
	JSON_GET_PARAM(jsonData, activeInHierarchy, getBool);

	JSON_GET_PARAM(jsonData, isStatic, getBool);
	JSON_GET_PARAM(jsonData, lightMapStatic, getBool);
	JSON_GET_PARAM(jsonData, navigationStatic, getBool);
	JSON_GET_PARAM(jsonData, occluderStatic, getBool);
	JSON_GET_PARAM(jsonData, occludeeStatic, getBool);

	JSON_GET_PARAM(jsonData, nameClash, getBool);
	JSON_GET_PARAM(jsonData, uniqueName, getString);

	JSON_GET_PARAM(jsonData, prefabRootId, getInt);
	JSON_GET_PARAM(jsonData, prefabObjectId, getInt);
	JSON_GET_PARAM(jsonData, prefabInstance, getBool);
	JSON_GET_PARAM(jsonData, prefabModelInstance, getBool);
	JSON_GET_PARAM(jsonData, prefabType, getString);

	renderers.Empty();
	skinRenderers.Empty();
	lights.Empty();
	probes.Empty();

	getJsonObjArray(jsonData, lights, "light", true);
	getJsonObjArray(jsonData, renderers, "renderer", true);
	getJsonObjArray(jsonData, probes, "reflectionProbes", true);
	getJsonObjArray(jsonData, terrains, "terrains", true);
	getJsonObjArray(jsonData, skinRenderers, "skinRenderers", true);
	getJsonObjArray(jsonData, animators, "animators", true);

	getJsonObjArray(jsonData, colliders, "colliders", true);
	getJsonObjArray(jsonData, rigidbodies, "rigidbodies", true);

	getJsonObjArray(jsonData, joints, "joints", true);

	if (nameClash && (uniqueName.Len() > 0)){
		UE_LOG(JsonLog, Warning, TEXT("Name clash detected on object %d: %s. Renaming to %s"), 
			id, *name, *uniqueName);		
		ueName = uniqueName;
	}
	else
		ueName = name;

	ueWorldMatrix = unityWorldToUe(worldMatrix);
}

IntArray JsonGameObject::getFirstMaterials() const{
	for(int i = 0; i < renderers.Num(); i++){
		const auto &curRend = renderers[i];
		if (curRend.hasMaterials())
			return curRend.materials;
	}
	UE_LOG(JsonLog, Warning, TEXT("Materials not found on renderer, returning blank array"));
	return IntArray();
}

FTransform JsonGameObject::getUnrealTransform(const FVector& localUnityOffset) const{
	using namespace UnrealUtilities;

	FTransform result;
	result.SetFromMatrix(unityWorldToUe(worldMatrix, localUnityOffset));
	return result;
}

FTransform JsonGameObject::getUnrealTransform() const{
	FTransform result;
	result.SetFromMatrix(ueWorldMatrix);
	return result;
}

FVector JsonGameObject::unityLocalVectorToUnrealWorld(const FVector &arg) const{
	using namespace UnrealUtilities;

	FVector x, y, z, pos;

	worldMatrix.GetScaledAxes(x, y, z);
	return unityVecToUe(arg.X * x + arg.Y * y + arg.Z * z);
}

FVector JsonGameObject::unityLocalPosToUnrealWorld(const FVector &arg) const{
	using namespace UnrealUtilities;

	FVector x, y, z, pos;
	worldMatrix.GetScaledAxes(x, y, z);
	pos = worldMatrix.GetOrigin();
	return unityPosToUe(arg.X * x + arg.Y * y + arg.Z * z + pos);
}

int JsonGameObject::findSuitableRootColliderIndex() const{
	for(int i = 0; i < colliders.Num(); i++){
		const auto& cur = colliders[i];
		if (!cur.isMeshCollider() && (cur.center == FVector::ZeroVector))
			return i;
	}
	return -1;
}

int JsonGameObject::findMainMeshColliderIndex() const{
	if (!meshId.isValid())
		return -1;//magic number...
	for (int i = 0; i < colliders.Num(); i++){
		const auto &cur = colliders[i];
		if (cur.isMeshCollider() && (cur.meshId == meshId))
			return i;
	}

	return -1;
}

const JsonCollider* JsonGameObject::getMainMeshCollider() const{
	return getColliderByIndex(findMainMeshColliderIndex());
}

bool JsonGameObject::hasMainMeshCollider() const{
	return getMainMeshCollider() != nullptr;
}

const JsonCollider* JsonGameObject::getColliderByIndex(int index) const{
	if (index < 0)
		return nullptr;
	return &colliders[index];
}

const JsonRenderer* JsonGameObject::getFirstRenderer() const{
	if (renderers.Num() > 0)
		return &renderers[0];
	return nullptr;
}

int JsonGameObject::getNumSpawnComponents() const{
	return lights.Num()
		+ probes.Num()
		+ renderers.Num()
		+ skinRenderers.Num()
		+ terrains.Num()
		//+ animators.Num() animators do not spawn components
		+ colliders.Num()
		+ rigidbodies.Num();
}

int JsonGameObject::getNumComponents() const{
	return lights.Num() 
		+ probes.Num()
		+ renderers.Num() 
		+ skinRenderers.Num()
		+ terrains.Num() 
		+ animators.Num()
		+ colliders.Num() 
		+ rigidbodies.Num();
}

EComponentMobility::Type JsonGameObject::getUnrealMobility() const{
	if (isStatic)
		return EComponentMobility::Static;
	return EComponentMobility::Movable;
}

bool JsonGameObject::usesPrefab() const{
	return (prefabRootId >= 0) && (prefabObjectId >= 0);
}

bool JsonGameObject::isPrefabRoot() const{
	return usesPrefab() && (prefabObjectId == 0);
}
