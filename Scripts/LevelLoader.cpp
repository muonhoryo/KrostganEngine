
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

	Texture* tex=nullptr;

	{
		UnitObject* unit = nullptr;
		for (UnitLoadInfo* un : levelInfo.Units) {

			unit = &LoadUnit(*un, tex);
			LoadedUnits.push_front(unit);
			LoadedGraphics.push_front(unit);
		}
	}
	{
		HeroObject* hero = nullptr;
		for (HeroLoadInfo* he : levelInfo.Heroes) {

			hero = &LoadHero(*he, tex);
			LoadedUnits.push_front((UnitObject*)hero);
			LoadedHeroes.push_front(hero);
			LoadedGraphics.push_front((ICallbackRec_GraphRen*)hero);
		}

		HeroesLoadEventArgs& heArgs = *new HeroesLoadEventArgs(&LoadedHeroes);
		HeroesLoadEventHan.Execute(heArgs);

		UnitsLoadEventArgs& unArgs = *new UnitsLoadEventArgs(&LoadedUnits);
		UnitsLoadEventHan.Execute(unArgs);
	}
	{
		WallObject* wall = nullptr;
		for (WallLoadInfo* wl : levelInfo.Walls) {

			wall = &LoadWall(*wl, tex);
			LoadedWalls.push_front(wall);
			LoadedGraphics.push_front(wall);
		}

		WallsLoadEventArgs& wlArgs = *new WallsLoadEventArgs(&LoadedWalls);
		WallsLoadEventHan.Execute(wlArgs);
	}

	GraphicsLoadEventArgs& gArgs = *new GraphicsLoadEventArgs(&LoadedGraphics);
	GraphicsLoadEventHan.Execute(gArgs);
}

UnitObjectCtorParams& LevelLoader::GetUnitParams(const UnitLoadInfo& info, Texture* texBuffer) {

	texBuffer = new Texture();
	texBuffer->loadFromFile(info.TexturePath);
	UnitObjectCtorParams& params = *new UnitObjectCtorParams();
	params.BattleStats = info.BattleStats;
	params.EntityFraction = info.EntityFraction;
	params.RenTexture = texBuffer;
	params.RenOffset = info.SpriteOffset;
	params.Position = info.Position;
	params.Size = info.Size;
	return params;
}
UnitObject& LevelLoader::LoadUnit(const UnitLoadInfo& info, Texture* texBuffer) {

	auto& params = GetUnitParams(info, texBuffer);
	UnitObject* unitObj = new UnitObject(params);
	delete& params;
	return *unitObj;
}
HeroObject& LevelLoader::LoadHero(const HeroLoadInfo& info,Texture* texBuffer) {
	UnitObjectCtorParams& unParams = GetUnitParams(info, texBuffer);
	HeroObjectCtorParams& params = *new HeroObjectCtorParams(unParams);
	delete &unParams;
	HeroObject* heroObj = new HeroObject(params);
	delete& params;
	return *heroObj;
}
WallObject& LevelLoader::LoadWall(const WallLoadInfo& info, Texture* texBuffer) {

	texBuffer = new Texture();
	texBuffer->loadFromFile(info.TexturePath);
	return *new WallObject(*texBuffer, info.SpriteOffset, info.Position, info.Size);
}