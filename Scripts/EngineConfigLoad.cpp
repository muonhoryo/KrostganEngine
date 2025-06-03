
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
		unsigned int XRes;
		unsigned int YRes;

		if (!TryGetValue(EngineConfig::DEF_X_WINDOW_RESOLUTION, &buffer))
			throw exception("Cannot parse window's XResolution");
		XRes = stoi(buffer);

		if (!TryGetValue(EngineConfig::DEF_Y_WINDOW_RESOLUTION, &buffer))
			throw exception("Cannot parse window's YResolution");
		YRes = stoi(buffer);

		LoadedConfig.WindowResolution = Vector2f(XRes, YRes);
	}

	//

	if (!TryGetValue(EngineConfig::DEF_FRAMERATE_LIMIT, &buffer))
		throw exception("Cannot pars framerate limit");
	LoadedConfig.FrameRateLimit = stoi(buffer);

	if (!TryGetValue(EngineConfig::DEF_CURSOR_ATTACK_HOTSPOT, &buffer))
		throw exception("Cannot parse attack cursor hotspot");
	LoadedConfig.CursorHotspot_Attack = ParseVec2u(buffer);

	if (!TryGetValue(EngineConfig::DEF_CAMERA_MOVING_SPEED, &buffer))
		throw exception("Cannot parse camera moving speed");
	LoadedConfig.Camera_MovSpeed = stof(buffer);

	//Camera moving borders

	{
		float right, left, top, bottom;
		
		if (!TryGetValue(EngineConfig::DEF_CAMERA_MOV_AREA_LEFT, &buffer))
			throw exception("Cannot parse camera moving left border");
		left = stof(buffer);

		if (!TryGetValue(EngineConfig::DEF_CAMERA_MOV_AREA_RIGHT, &buffer))
			throw exception("Cannot parse camera moving right border");
		right= stof(buffer);

		if (!TryGetValue(EngineConfig::DEF_CAMERA_MOV_AREA_TOP, &buffer))
			throw exception("Cannot parse camera moving top border");
		top = stof(buffer);

		if (!TryGetValue(EngineConfig::DEF_CAMERA_MOV_AREA_BOTTOM, &buffer))
			throw exception("Cannot parse camera moving bottom border");
		bottom = stof(buffer);

		LoadedConfig.CameraMovingArea = Rect<float>(left, top, right-left, bottom-top);
	}

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