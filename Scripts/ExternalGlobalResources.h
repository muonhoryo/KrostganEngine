#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	struct ExternalGlobalResources {

		ExternalGlobalResources(Texture& UnitsSelectionAreaSprite,
			Texture& HeroesSelectionAreaSprite)
			: UnitsSelectionAreaSprite(UnitsSelectionAreaSprite),
			HeroesSelectionAreaSprite(HeroesSelectionAreaSprite)
		{}

		Texture& UnitsSelectionAreaSprite;
		Texture& HeroesSelectionAreaSprite;

		static inline const string DEF_UNITS_SELECTIONAREA_SPRITE_PATH = "UnitsSelectionAreaSprPath";
		static inline const string DEF_HEROES_SELECTIONAREA_SPRITE_PATH = "HeroesSelectionAreaSprPath";
	};
}