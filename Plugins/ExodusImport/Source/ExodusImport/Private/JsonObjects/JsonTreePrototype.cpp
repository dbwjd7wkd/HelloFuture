#include "JsonImportPrivatePCH.h"
#include "JsonTreePrototype.h"
#include "macros.h"

//#define JSON_ENABLE_VALUE_LOGGING

using namespace JsonObjects;

JsonTreePrototype::JsonTreePrototype(JsonObjPtr data){
	load(data);
}

void JsonTreePrototype::load(JsonObjPtr data){
	JSON_GET_VAR(data, prefabId);
	JSON_GET_VAR(data, prefabObjectId);
	JSON_GET_VAR(data, meshId);
	JSON_GET_VAR(data, materials);
}
