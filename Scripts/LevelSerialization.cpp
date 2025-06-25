
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

				if (line.find(LevelCellMapDeser::LEVEL_CELL_MAP_END) != string::npos) {

					params.push_back(line);
					map=&LevelCellMapDeser::Deserialize(params, &columnCount);

					//LevelCellMapDeser::CellInfo* el=nullptr;
					//float step = Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution;

					//for (int i = 0;i < res.size();++i) {
					//	for (int j = 0;j < columnCount;++j) {
					//		if (j < res[i]->size()) {
					//			el = (*res[i])[j];
					//			if (el->CatalogID != LevelCellMapDeser::EMPTY_CATALOG_ID) {

					//				ObjectsCatalog::GetObjectInfo(el->CatalogID)->InstanceObject(levelInfo,
					//					Vector2f(j * step, i * step),
					//					&el->AdditionalParams);
					//			}
					//			delete el;
					//		}
					//	}
					//	delete res[i];
					//}

					//for (vector<LevelCellMapDeser::CellInfo*>* vec : res) {
					//	for (LevelCellMapDeser::CellInfo* inf : *vec) {
					//		delete inf;
					//	}
					//	vec->clear();
					//	delete vec;
					//}
					//res.clear();
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
