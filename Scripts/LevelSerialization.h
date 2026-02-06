#pragma once

#include <_LevelLoading.h>
#include <string>
#include <EntityBattleStats.h>
#include <forward_list>
#include <vector>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {
	class LevelSerialization {
	public:
		static LevelLoadingInfo& DeserializeLevel(const string& serPath);
		static void SerializeLevel(string serPath, LevelLoadingInfo levelInfo);

		static inline const string UNIQUE_OBJECTS_HEADER = "UniqueObjects:";

		static inline const string DEF_CAMERA_BORDERS_AREA_LEFT		= "Camera_Borders_Left";
		static inline const string DEF_CAMERA_BORDERS_AREA_RIGHT	= "Camera_Borders_Right";
		static inline const string DEF_CAMERA_BORDERS_AREA_TOP		= "Camera_Borders_Top";
		static inline const string DEF_CAMERA_BORDERS_AREA_BOTTOM	= "Camera_Borders_Bottom";
		static inline const string DEF_CAMERA_STARTPOS				= "CameraStartPos";

		static inline const string DEF_WARFOG_OFFSET		= "WarFogOffset";
		static inline const string DEF_WARFOG_SHADER_PATH	= "WarFogShaderPath";

		static inline const string DEF_BG_IMAGE_PATH	= "BG_ImagePath";
		static inline const string DEF_BG_TILED			= "BG_Tiled";


	private:
		LevelSerialization() {}
	};
}