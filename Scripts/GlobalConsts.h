#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace KrostganEngine::Core {
	struct GlobalConsts {
		~GlobalConsts() {
			cout << "delete" << endl;
		}

		float GameObjs_OneSizeSpriteResolution;
		float HeroesSelectArea_OneSizeSpriteResol;
		float UnitsSelectArea_OneSizeSpriteResol;
		float EPS;

		static inline const string DEF_GAMEOBJS_ONESIZE_SPRITERESOL = "GameObjs_OneSizeSpriteResol";
		static inline const string DEF_HEROES_SELECTAREA_ONESIZE_SPRITERESOL = "HeroesSelectArea_OneSizeSpriteResol";
		static inline const string DEF_UNITS_SELECTAREA_ONESIZE_SPRITERESOL = "UnitsSelectArea_OneSizeSpriteResol";
		static inline const string DEF_EPS = "EPS";
	};
}