#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <string>
#include <EntityBattleStats.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine {
	namespace Core {
		struct UnitLoadInfo {
			UnitLoadInfo(string Name, string TexturePath, Vector2f SpriteOffset, Vector2f Position, float Size,
				EntityBattleStats& BattleStats);

			string Name;
			string TexturePath;
			Vector2f SpriteOffset;
			Vector2f Position;
			float Size;
			EntityBattleStats& BattleStats;
		};
		struct LevelLoadingInfo {

			forward_list<UnitLoadInfo>& Units;

			LevelLoadingInfo(forward_list<UnitLoadInfo>& Units);
		};
	}
}


