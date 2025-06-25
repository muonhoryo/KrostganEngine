
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
	for (int i = 0;i < levelInfo.LevelMap.size();++i) {
		for (int j = 0;j < (*levelInfo.LevelMap[i]).size();++j) {
			cell = (*levelInfo.LevelMap[i])[j];
			if (cell->CatalogID != LevelCellMapDeser::EMPTY_CATALOG_ID) {

				ObjectsCatalog::GetObjectInfo(cell->CatalogID)->InstanceObject(*LoadedLevel,
					LevelCellMapDeser::GetCellGlobalPosition(Vector2u(i,j)),
					&cell->AdditionalParams);
			}
		}
	}

	for (auto obj : levelInfo.UniqueObjects) {
		obj->InstanceObject(*LoadedLevel);
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