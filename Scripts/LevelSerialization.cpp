
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

LevelLoadingInfo& LevelSerialization::DeserializeLevel(string serPath) {

	LevelLoadingInfo* info = nullptr;
	vector<vector<LvlObjInstantiationInfo*>*>* map = nullptr;
	forward_list<WorldObjectLoadInfo*>& uniqueObjects = *new forward_list<WorldObjectLoadInfo*>();
	bool isDeserObstrMap = false;
	bool mapDeserialized = false;

	string line;
	ifstream st(serPath);
	vector<string>& params = *new vector<string>();
	WorldObjectLoadInfo* uniqObj = nullptr;
	size_t columnCount = 0;
	if (st.is_open()) {
		while (getline(st, line)) {

			if (isDeserObstrMap) {

				if (line.find(LevelCellMapDeser::LVL_CMAP_END) != string::npos) {

					params.push_back(line);
					map=&LevelCellMapDeser::Deserialize(params, columnCount);
					isDeserObstrMap = false;
					mapDeserialized = true;
					params.clear();
					break;
				}
				else {

					params.push_back(line);
				}
			}
			else {

				if (line.find(ObjsCatalogDeserial::OBJECTS_SEP_LINE) != string::npos) {

					uniqObj=&ObjsCatalogDeserial::ParseObjInfo(params);
					if (uniqObj != nullptr)
						uniqueObjects.push_front(uniqObj);
					params.clear();
				}
				else if (line.find(LevelCellMapDeser::DEF_LEVEL_CELL_MAP) != string::npos) {

					if (mapDeserialized)
						throw exception("Map is already loaded");

					isDeserObstrMap = true;
					params.push_back(line);
				}
				else {

					params.push_back(line);
				}
			}
		}

		if (map == nullptr)
			map = new vector<vector<LvlObjInstantiationInfo*>*>();

		info = new LevelLoadingInfo(*map, uniqueObjects);

		info->MapRowsCount = map->size();
		info->MapColumnsCount = columnCount;

		const pair<const string, const string>* pr=nullptr;
		float left=0;
		float right=0;
		float top = 0;
		float bottom = 0;
		while (getline(st, line)) {

			pr = ObjsCatalogDeserial::ParseParamLine(line);
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
		}
		info->CameraBorders = Rect<float>(left, top, right - left, bottom - top);
	}

	if (info == nullptr)
		throw exception("Cant read file");

	return *info;
}
