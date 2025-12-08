#pragma once

#include <LevelLoading.h>
#include <string>
#include <EntityBattleStats.h>
#include <forward_list>
#include <vector>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {
	class LevelSerialization {
	public:
		static LevelLoadingInfo& DeserializeLevel(string serPath);
		static void SerializeLevel(string serPath, LevelLoadingInfo levelInfo);

		static inline const string DEF_CAMERA_BORDERS_AREA_LEFT = "Camera_Borders_Left";
		static inline const string DEF_CAMERA_BORDERS_AREA_RIGHT = "Camera_Borders_Right";
		static inline const string DEF_CAMERA_BORDERS_AREA_TOP = "Camera_Borders_Top";
		static inline const string DEF_CAMERA_BORDERS_AREA_BOTTOM = "Camera_Borders_Bottom";
		
		static inline const string DEF_WARFOG_OFFSET = "WarFogOffset";

		static inline const string DEF_WARFOG_SHADER_PATH = "WarFogShaderPath";

	private:
		LevelSerialization() {}
	};
}