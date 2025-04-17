#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <forward_list>
#include <string>

using namespace std;
using namespace sf;

namespace KrostganEngine {
	namespace Core {
		struct UnitLoadInfo {

			string TexturePath;
			Vector2f SpriteOffset;
			Vector2f Position;

			UnitLoadInfo(string TexturePath, Vector2f SpriteOffset, Vector2f Position);
		};
		struct LevelLoadingInfo {

			forward_list<UnitLoadInfo> Units;

			LevelLoadingInfo(forward_list<UnitLoadInfo> Units);
		};
	}
}


