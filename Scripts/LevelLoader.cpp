
#include <EngineCore.h>
#include <CoreGameObjects.h>
#include <forward_list>
#include <SFML/Graphics.hpp>
#include <string>
#include <Events.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

void LevelLoader::LoadLevel(const LevelLoadingInfo& levelInfo) {

	LvlObjInstantiationInfo* cell = nullptr;
	WorldTransfObj* obj = nullptr;
	WorldObjectLoadInfo* objInfo = nullptr;
	LvlObjAdditParams* subInfo = nullptr;
	for (int i = 0;i < levelInfo.LevelMap.size();++i) {
		for (int j = 0;j < (*levelInfo.LevelMap[i]).size();++j) {
			cell = (*levelInfo.LevelMap[i])[j];
			if (cell->CatalogID != ObjectsCatalog::EMPTY_CATALOG_ID) {

				if (cell->CatalogSubID!= ObjectsCatalog::ABSENT_SUB_CATALOG_ID) {
					subInfo = ObjectsCatalog::GetSubObjInfo(cell->CatalogID, cell->CatalogSubID);
				}

				objInfo = ObjectsCatalog::GetObjectInfo(cell->CatalogID);
				obj = objInfo->InstantiateObject(subInfo, cell->AdditParams);
				if((Vector2i)obj->GetGlobalPosition()== ITransformableObj::NULL_POS)
					obj->SetGlobalPosition(LevelCellMapDeser::GetCellGlobalPosition(Vector2u(i, j)));
				subInfo = nullptr;

				cout << ObjectsCatalog::GetObjectInfo(cell->CatalogID)->Name << ": " << to_string(obj->GetGlobalPosition()) << endl;
			}
		}
	}

	for (auto obj : levelInfo.UniqueObjects) {

		auto insObj=obj->InstantiateObject();

		cout << obj->Name << ": " << to_string(insObj->GetGlobalPosition()) << endl;
	}

	LevelBypassMapManager::LoadFromLevelMap(levelInfo.LevelMap);

	LevelManager::AssignLevelInfo(levelInfo);
}