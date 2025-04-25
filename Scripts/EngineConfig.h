#pragma once

#include <string>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

namespace KrostganEngine::Core {
	struct EngineConfig {

		Vector2f WindowResolution;

		static inline const string DEF_X_WINDOW_RESOLUTION = "X_Window_Resolution";
		static inline const string DEF_Y_WINDOW_RESOLUTION = "Y_Window_Resolution";
	};
}