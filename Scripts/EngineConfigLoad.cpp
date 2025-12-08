
#include <string>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <EngineCore.h>
#include <Extensions.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;

EngineConfigLoad::EngineConfigLoad() :ValuesListDeserializer(),
	LoadedConfig(*new EngineConfig()){
}

const EngineConfig& EngineConfigLoad::LoadEngineConfig() {
	DeserializeValues();

	string buffer = string();

	//Window resolution

	{
		unsigned int XRes = DeserValueByDef_uint(EngineConfig::DEF_X_WINDOW_RESOLUTION, buffer);
		unsigned int YRes = DeserValueByDef_uint(EngineConfig::DEF_Y_WINDOW_RESOLUTION, buffer);

		LoadedConfig.WindowResolution = Vector2u(XRes, YRes);
	}

	//

	LoadedConfig.FrameRateLimit			= DeserValueByDef_int	(EngineConfig::DEF_FRAMERATE_LIMIT, buffer);
	LoadedConfig.CursorHotspot_Attack	= DeserValueByDef_Vec2u	(EngineConfig::DEF_CURSOR_ATTACK_HOTSPOT, buffer);
	LoadedConfig.Camera_MovSpeed		= DeserValueByDef_float	(EngineConfig::DEF_CAMERA_MOVING_SPEED, buffer);

	GetValueByDef(EngineConfig::DEF_WARFOG_STENCIL_SHADER_PATH, buffer);
	FStreamExts::ClearPath(buffer);
	LoadedConfig.WarForStencilShaderPath = buffer;

	//

	StrValuesArr.clear();
	return LoadedConfig;
}
const EngineConfig& EngineConfigLoad::GetLoadedConfig() {
	return LoadedConfig;
}

const string EngineConfigLoad::GetFilePath() {
	return CONFIG_PATH;
}
const char EngineConfigLoad::GetValuesDefEndSym() {
	return CONFIG_DEF_END_SYM;
}

const string EngineConfigLoad::CONFIG_PATH = "Config.txt";
const char EngineConfigLoad::CONFIG_DEF_END_SYM = ':';