#pragma once

#include "JsonTypes.h"
#include "JsonLog.h"

#include "JsonObjects/JsonBounds.h"
#include "JsonObjects/JsonGameObject.h"
#include "JsonObjects/JsonLight.h"
#include "JsonObjects/JsonMaterial.h"
#include "JsonObjects/JsonPrefabData.h"
#include "JsonObjects/JsonReflectionProbe.h"
#include "JsonObjects/JsonRenderer.h"
#include "JsonObjects/JsonTerrain.h"
#include "JsonObjects/JsonTerrainDetailPrototype.h"
#include "JsonObjects/JsonAnimation.h"
#include "JsonObjects/macros.h"
#include "JsonObjects/loggers.h"
#include "JsonObjects/getters.h"
#include "JsonObjects/utilities.h"

#include "JsonObjects/JsonTexture.h"
#include "JsonObjects/JsonCubemap.h"
#include "JsonObjects/JsonMesh.h"
#include "JsonObjects/JsonExternResourceList.h"
#include "JsonObjects/JsonProject.h"
#include "JsonObjects/JsonScene.h"
#include "JsonObjects/JsonAnimation.h"

#include "JsonObjects/JsonPhysics.h"

namespace JsonObjects{
	JsonObjPtr loadJsonFromFile(const FString &filename);
}
