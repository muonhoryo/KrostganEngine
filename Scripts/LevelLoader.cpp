
#pragma once

#include <GameObjects.h>
#include <LevelLoadingInfo.h>
#include <LevelLoader.h>
#include <forward_list>
#include <SFML/Graphics.hpp>
#include <string>
#include <Event.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine;

UnitsLoadEventArgs::UnitsLoadEventArgs(forward_list<UnitObject>* LoadedUnits) {
	this->LoadedUnits = LoadedUnits;
}

ExecutedEvent<UnitsLoadEventArgs> LevelLoader::UnitsLoadEvent = ExecutedEvent<UnitsLoadEventArgs>();
//EventHandler< UnitsLoadEventArgs> LevelLoader::UnitsLoadEventHan = EventHandler<UnitsLoadEventArgs>(LevelLoader::UnitsLoadEvent);
forward_list <UnitObject > LevelLoader::LoadedUnits = forward_list<UnitObject>();
void LevelLoader::LoadLevel(const LevelLoadingInfo& levelInfo) {
	
	/*for (auto un : levelInfo.Units) {
		Texture tex;
		tex.loadFromFile(un.TexturePath);
		const Texture& texRef =tex;
		auto unitObj = new UnitObject(texRef,un.SpriteOffset,un.Position);
		LoadedUnits.push_front(*unitObj);
	}*/

	//UnitsLoadEventHan.Execute(LoadedUnits);
}
