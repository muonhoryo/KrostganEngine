#pragma once

#include <string>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;

namespace KrostganEngine::Core {
	struct EngineConfig {

		Vector2f WindowResolution;
		unsigned int FrameRateLimit;
		Vector2u CursorHotspot_Attack;
		float Camera_MovSpeed;
		Rect<float> CameraMovingArea;

		static inline const string DEF_X_WINDOW_RESOLUTION = "X_Window_Resolution";
		static inline const string DEF_Y_WINDOW_RESOLUTION = "Y_Window_Resolution";
		static inline const string DEF_FRAMERATE_LIMIT = "FrameRate_Limit";
		static inline const string DEF_CURSOR_ATTACK_HOTSPOT = "CursorHotspot_Attack";
		static inline const string DEF_CAMERA_MOVING_SPEED = "Camera_MovSpeed";
		static inline const string DEF_CAMERA_MOV_AREA_LEFT = "Camera_MovArea_Left";
		static inline const string DEF_CAMERA_MOV_AREA_RIGHT = "Camera_MovArea_Right";
		static inline const string DEF_CAMERA_MOV_AREA_TOP = "Camera_MovArea_Top";
		static inline const string DEF_CAMERA_MOV_AREA_BOTTOM = "Camera_MovArea_Bottom";
	};
}