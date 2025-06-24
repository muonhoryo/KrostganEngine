#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <string>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>
#include <CoreGameObjects.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::Core {
	struct GameObjectLoadInfo {
		GameObjectLoadInfo(){}
		string Name="";
		string TexturePath="";
		Vector2f SpriteOffset=Vector2f(0,0);
		Vector2f Position = Vector2f(0, 0);
		float Size = 1;
	};
	struct UnitLoadInfo : public GameObjectLoadInfo {
		UnitLoadInfo() :GameObjectLoadInfo(),BattleStats(nullptr) {};

		EntityBattleStats* BattleStats;
		Fraction EntityFraction=Fraction::Neutral;
	};
	struct HeroLoadInfo : public UnitLoadInfo {
		HeroLoadInfo():UnitLoadInfo(){}
	};
	struct WallLoadInfo :public GameObjectLoadInfo {
		WallLoadInfo() : GameObjectLoadInfo() {};
	};
	struct LevelLoadingInfo final {

		forward_list<UnitLoadInfo*>& Units;
		forward_list<HeroLoadInfo*>& Heroes;
		forward_list<WallLoadInfo*>& Walls;

		LevelLoadingInfo(forward_list<UnitLoadInfo*>& Units,forward_list<HeroLoadInfo*>& Heroes ,forward_list<WallLoadInfo*>& Walls) 
			:Units(Units),
			Heroes(Heroes),
			Walls(Walls)
		{}
		~LevelLoadingInfo();
	};
}


