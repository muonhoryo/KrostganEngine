#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	struct ExternalGlobalResources {

		ExternalGlobalResources(){}

		Texture* UnitsSelectionAreaSprite=nullptr;
		Texture* HeroesSelectionAreaSprite=nullptr;
		Texture* CursorSprite_Attack = nullptr;
		Texture* UnitDeathEffectSprite=nullptr;
		Font* DefaultFont=nullptr;

		static inline const string DEF_UNITS_SELECTIONAREA_SPRITE_PATH = "UnitsSelectionAreaSprPath";
		static inline const string DEF_HEROES_SELECTIONAREA_SPRITE_PATH = "HeroesSelectionAreaSprPath";
		static inline const string DEF_CURSOR_ATTACK_SPRITE_PATH = "CursorSprite_Attack";
		static inline const string DEF_UNIT_DEATHEFFECT_SPRITE_PATH = "UnitDeathEffectSprite";
		static inline const string DEF_DEFAULT_FONT_PATH = "DefaultFont";
	};
}