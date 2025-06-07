
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
WallsLoadEventArgs::WallsLoadEventArgs(forward_list<WallObject*>* LoadedWalls) {
	this->LoadedWalls = LoadedWalls;
}

void LevelLoader::LoadLevel(const LevelLoadingInfo& levelInfo) {

	Texture* tex; {

		UnitObject* unitObj;
		for (UnitLoadInfo* un : levelInfo.Units) {
			tex = new Texture();
			tex->loadFromFile(un->TexturePath);
			UnitObjectCtorParams& params = *new UnitObjectCtorParams();
			params.BattleStats = un->BattleStats;
			params.EntityFraction = un->EntityFraction;
			params.RenTexture = tex;
			params.RenOffset = un->SpriteOffset;
			params.Position = un->Position;
			params.Size = un->Size;
			unitObj = new UnitObject(params);
			delete& params;
			LoadedUnits.push_front(unitObj);
		}
		for (UnitObject* un : LoadedUnits) {
			LoadedGraphics.push_front(un);
		}
	}
	UnitsLoadEventArgs& unArgs = *new UnitsLoadEventArgs(&LoadedUnits);
	UnitsLoadEventHan.Execute(unArgs);

	{
		WallObject* wallObj;
		for (WallLoadInfo* wl : levelInfo.Walls) {
			tex = new Texture();
			tex->loadFromFile(wl->TexturePath);
			wallObj = new WallObject(*tex, wl->SpriteOffset, wl->Position, wl->Size);
			LoadedWalls.push_front(wallObj);
		}
		for (WallObject* wl : LoadedWalls) {
			LoadedGraphics.push_front(wl);
		}
	}
	WallsLoadEventArgs& wlArgs = *new WallsLoadEventArgs(&LoadedWalls);
	WallsLoadEventHan.Execute(wlArgs);

	GraphicsLoadEventArgs& gArgs = *new GraphicsLoadEventArgs(&LoadedGraphics);
	GraphicsLoadEventHan.Execute(gArgs);
}
