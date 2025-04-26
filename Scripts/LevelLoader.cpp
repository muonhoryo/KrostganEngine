
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

UnitsLoadEventArgs::UnitsLoadEventArgs(forward_list<UnitObject*>* LoadedUnits) {
	this->LoadedUnits = LoadedUnits;
}
GraphicsLoadEventArgs::GraphicsLoadEventArgs(forward_list<ICallbackRec_GraphRen*>* LoadedGraphics) {
	this->LoadedGraphics = LoadedGraphics;
}

ExecutedEvent<UnitsLoadEventArgs> LevelLoader::UnitsLoadEvent = ExecutedEvent<UnitsLoadEventArgs>();
ExecutedEvent<GraphicsLoadEventArgs> LevelLoader::GraphicsLoadEvent = ExecutedEvent<GraphicsLoadEventArgs>();

EventHandler< UnitsLoadEventArgs> LevelLoader::UnitsLoadEventHan = EventHandler<UnitsLoadEventArgs>(LevelLoader::UnitsLoadEvent);
EventHandler<GraphicsLoadEventArgs> LevelLoader::GraphicsLoadEventHan = EventHandler<GraphicsLoadEventArgs>(LevelLoader::GraphicsLoadEvent);

forward_list <UnitObject* > LevelLoader::LoadedUnits = forward_list<UnitObject*>();
forward_list <ICallbackRec_GraphRen*> LevelLoader::LoadedGraphics = forward_list<ICallbackRec_GraphRen*>();

void LevelLoader::LoadLevel(const LevelLoadingInfo& levelInfo) {

	Texture* tex;
	UnitObject* unitObj;
	
	for (auto& un : levelInfo.Units) {
		tex = new Texture();
		tex->loadFromFile(un.TexturePath);
		unitObj = new UnitObject(*tex,un.SpriteOffset,un.Position,un.Size);
		LoadedUnits.push_front(unitObj);
	}
	for (UnitObject* un : LoadedUnits) {
		LoadedGraphics.push_front(un);
	}
	UnitsLoadEventArgs& args = *new UnitsLoadEventArgs(&LoadedUnits);
	UnitsLoadEventHan.Execute(args);
	
	GraphicsLoadEventArgs& gArgs = *new GraphicsLoadEventArgs(&LoadedGraphics);
	GraphicsLoadEventHan.Execute(gArgs);
}
