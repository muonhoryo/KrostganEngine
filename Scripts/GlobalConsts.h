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

		static inline const string DEF_GAMEOBJS_ONESIZE_SPRITERESOL = "GameObjs_OneSizeSpriteResol";
	};
}