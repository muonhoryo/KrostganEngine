
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

	if (LoadedLevel != nullptr)
		delete LoadedLevel;
	LoadedLevel = new LoadedObjects();

	LevelCellMapDeser::CellInfo* cell = nullptr;
	GameObject* obj = nullptr;
	GameObjectLoadInfo* objInfo = nullptr;
	LvlObjCatalogSubInfo* subInfo = nullptr;
	for (int i = 0;i < levelInfo.LevelMap.size();++i) {
		for (int j = 0;j < (*levelInfo.LevelMap[i]).size();++j) {
			cell = (*levelInfo.LevelMap[i])[j];
			if (cell->CatalogID != ObjectsCatalog::EMPTY_CATALOG_ID) {

				if (cell->SubCatalogID != ObjectsCatalog::ABSENT_SUB_CATALOG_ID) {
					subInfo = ObjectsCatalog::GetSubObjInfo(cell->CatalogID, cell->SubCatalogID);
				}

				objInfo = ObjectsCatalog::GetObjectInfo(cell->CatalogID);
				obj = objInfo->InstanceObject(*LoadedLevel, &cell->AdditionalParams, subInfo);
				if((Vector2i)obj->GetGlobalPosition()== ITransformableObj::NULL_POS)
					obj->SetGlobalPosition(LevelCellMapDeser::GetCellGlobalPosition(Vector2u(i, j)));
				subInfo = nullptr;

				cout << ObjectsCatalog::GetObjectInfo(cell->CatalogID)->Name << ": " << to_string(obj->GetGlobalPosition()) << endl;
			}
		}
	}

	for (auto obj : levelInfo.UniqueObjects) {

		auto insObj=obj->InstanceObject(*LoadedLevel);

		cout << obj->Name << ": " << to_string(insObj->GetGlobalPosition()) << endl;
	}

	HeroesLoadEventArgs& heArgs = *new HeroesLoadEventArgs(&LoadedLevel->LoadedHeroes);
	HeroesLoadEventHan.Execute(heArgs);

	UnitsLoadEventArgs& unArgs = *new UnitsLoadEventArgs(&LoadedLevel->LoadedUnits);
	UnitsLoadEventHan.Execute(unArgs);

	WallsLoadEventArgs& wlArgs = *new WallsLoadEventArgs(&LoadedLevel->LoadedWalls);
	WallsLoadEventHan.Execute(wlArgs);

	GraphicsLoadEventArgs& gArgs = *new GraphicsLoadEventArgs(&LoadedLevel->LoadedGraphics);
	GraphicsLoadEventHan.Execute(gArgs);

	LevelBypassMapManager::LoadFromLevelMap(levelInfo.LevelMap);
}