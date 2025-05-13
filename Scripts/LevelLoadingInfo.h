#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <string>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::Core {
	struct UnitLoadInfo {
		UnitLoadInfo(string Name, string TexturePath, Vector2f SpriteOffset, Vector2f Position, float Size,
			EntityBattleStats& BattleStats, Fraction EntityFraction);

		string Name;
		string TexturePath;
		Vector2f SpriteOffset;
		Vector2f Position;
		float Size;
		EntityBattleStats& BattleStats;
		Fraction EntityFraction;
	};
	struct LevelLoadingInfo {

		forward_list<UnitLoadInfo>& Units;

		LevelLoadingInfo(forward_list<UnitLoadInfo>& Units);
	};
}


