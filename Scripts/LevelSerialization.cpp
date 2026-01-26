
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Extensions.h>
#include <EngineCore.h>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

LevelLoadingInfo& LevelSerialization::DeserializeLevel(const string& serPath) {

	LevelLoadingInfo* info = nullptr;
	vector<vector<LvlObjInstantiationInfo*>*>* map = nullptr;
	forward_list<LvlObjInstantiationInfo*>& uniqueObjects = *new forward_list<LvlObjInstantiationInfo*>();

	string line;
	ifstream st(serPath);
	vector<string>& params = *new vector<string>();
	size_t columnCount = 0;

	while (getline(st, line)) {

		//Deserialize level cell map

		if (line.find(LevelCellMapDeser::LVL_CMAP_END) != string::npos) {

			params.push_back(line);
			map = &LevelCellMapDeser::Deserialize(params, columnCount);
			params.clear();
			break;
		}
		else {

			params.push_back(line);
		}
	}

	if (map == nullptr)
		map = new vector<vector<LvlObjInstantiationInfo*>*>();

	info = new LevelLoadingInfo(*map, uniqueObjects);

	info->MapRowsCount = map->size();
	info->MapColumnsCount = columnCount;

	const pair<const string, const string>* pr = nullptr;
	float left = 0;
	float right = 0;
	float top = 0;
	float bottom = 0;

	bool foundUniqueObjs = false;

	while (getline(st, line)) {

		pr = WorldObjsCatalogDeserial::ParseParamLine(line);
		if (pr == nullptr)
			continue;

		//Rect
		if (pr->first == DEF_CAMERA_BORDERS_AREA_LEFT) {
			left = stof(pr->second);
		}
		else if (pr->first == DEF_CAMERA_BORDERS_AREA_RIGHT) {
			right = stof(pr->second);
		}
		else if (pr->first == DEF_CAMERA_BORDERS_AREA_TOP) {
			top = stof(pr->second);
		}
		else if (pr->first == DEF_CAMERA_BORDERS_AREA_BOTTOM) {
			bottom = stof(pr->second);
		}
		//float
		else if (pr->first == DEF_WARFOG_OFFSET) {
			info->WarFogOffset = stof(pr->second);
		}
		//string
		else if (pr->first == DEF_WARFOG_SHADER_PATH) {
			info->WarFogShaderPath = pr->second;
		}
		else if (pr->first == DEF_BG_IMAGE_PATH) {
			info->BackgroundImagePath = pr->second;
		}
		//bool
		else if (pr->first == DEF_BG_TILED) {
			info->BackgroundTiled = FStreamExts::ParseBool(pr->second);
		}

		//Check end of level parameters
		else if (line.find(LevelSerialization::UNIQUE_OBJECTS_HEADER) != string::npos) {

			foundUniqueObjs = true;
			break;
		}
	}
	info->CameraBorders = Rect<float>(left, top, right - left, bottom - top);

	if (foundUniqueObjs) {

		LvlObjInstantiationInfo* unObjInfo = nullptr;

		while (getline(st, line)) {

			unObjInfo = new LvlObjInstantiationInfo();
			unObjInfo->Deserialize(line);
			uniqueObjects.push_front(unObjInfo);
		}

	}
	params.clear();
	

	return *info;
}
