#pragma once

#include <string>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

namespace KrostganEngine::Core {
	struct EngineConfig {

		Vector2u WindowResolution;
		unsigned int FrameRateLimit;
		Vector2u CursorHotspot_Attack;
		float Camera_MovSpeed;
		string WarForStencilShaderPath;

		static inline const string DEF_X_WINDOW_RESOLUTION			= "X_Window_Resolution";
		static inline const string DEF_Y_WINDOW_RESOLUTION			= "Y_Window_Resolution";
		static inline const string DEF_FRAMERATE_LIMIT				= "FrameRate_Limit";
		static inline const string DEF_CURSOR_ATTACK_HOTSPOT		= "CursorHotspot_Attack";
		static inline const string DEF_CAMERA_MOVING_SPEED			= "Camera_MovSpeed";
		static inline const string DEF_WARFOG_STENCIL_SHADER_PATH	= "WarFogStencilShader";
	};
}