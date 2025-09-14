
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

	vector<vector<LevelCellMapDeser::CellInfo*>*>* map = nullptr;
	forward_list<GameObjectLoadInfo*>& uniqueObjects = *new forward_list<GameObjectLoadInfo*>();
	bool isDeserObstrMap = false;
	bool mapDeserialized = false;

	string line;
	ifstream st(serPath);
	vector<string>& params = *new vector<string>();
	GameObjectLoadInfo* uniqObj = nullptr;
	size_t columnCount = 0;
	if (st.is_open()) {
		while (getline(st, line)) {

			if (isDeserObstrMap) {

				if (line.find(LevelCellMapDeser::LVL_CMAP_END) != string::npos) {

					params.push_back(line);
					map=&LevelCellMapDeser::Deserialize(params, &columnCount);
					isDeserObstrMap = false;
					mapDeserialized = true;
					params.clear();
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
	}

	if (map == nullptr)
		map = new vector<vector<LevelCellMapDeser::CellInfo*>*>();

	return *new LevelLoadingInfo(*map,uniqueObjects, columnCount);
}
