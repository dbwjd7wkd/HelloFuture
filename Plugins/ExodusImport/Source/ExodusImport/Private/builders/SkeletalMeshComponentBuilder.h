#pragma once
#include "JsonTypes.h"
#include "ImportContext.h"
#include "ImportedObject.h"
#include "JsonObjects/JsonGameObject.h"

class JsonImporter;

class SkeletalMeshComponentBuilder{
public:
	static void processSkinMeshes(ImportContext &workData, const JsonGameObject &gameObj, 
		ImportedObject *parentObject, const FString &folderPath, ImportedObjectArray *createdObjects, JsonImporter *importer, 
		std::function<UObject*()> outerCreator);
	static ImportedObject processSkinRenderer(ImportContext &workData, const JsonGameObject &jsonGameObj, 
		const JsonSkinRenderer &skinRend, ImportedObject *parentObject, const FString &folderPath, JsonImporter *importer, 
		std::function<UObject*()> outerCreator);
};
