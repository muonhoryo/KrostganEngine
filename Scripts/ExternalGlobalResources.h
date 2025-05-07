#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	struct ExternalGlobalResources {

		ExternalGlobalResources(Texture& UnitsSelectionAreaSprite,
			Texture& HeroesSelectionAreaSprite,
			Texture& CursorSprite_Attack)
			: UnitsSelectionAreaSprite(UnitsSelectionAreaSprite),
			HeroesSelectionAreaSprite(HeroesSelectionAreaSprite),
			CursorSprite_Attack(CursorSprite_Attack)
		{}

		Texture& UnitsSelectionAreaSprite;
		Texture& HeroesSelectionAreaSprite;
		Texture& CursorSprite_Attack;

		static inline const string DEF_UNITS_SELECTIONAREA_SPRITE_PATH = "UnitsSelectionAreaSprPath";
		static inline const string DEF_HEROES_SELECTIONAREA_SPRITE_PATH = "HeroesSelectionAreaSprPath";
		static inline const string DEF_CURSOR_ATTACK_SPRITE_PATH = "CursorSprite_Attack";
	};
}