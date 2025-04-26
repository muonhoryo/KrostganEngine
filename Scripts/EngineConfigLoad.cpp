
#include <string>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>
#include <EngineCore.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::Core;

EngineConfigLoad::EngineConfigLoad() :ValuesListDeserializer() {
	LoadedConfig = EngineConfig();
}

const EngineConfig& EngineConfigLoad::LoadEngineConfig() {
	DeserializeValues();
	unsigned int XRes;
	unsigned int YRes;

	string line = string();
	if (!TryGetValue(EngineConfig::DEF_X_WINDOW_RESOLUTION, &line))
		throw exception("Cannot parse window's XResolution");
	XRes = stoi(line);

	if (!TryGetValue(EngineConfig::DEF_Y_WINDOW_RESOLUTION, &line))
		throw exception("Cannot parse window's YResolution");
	YRes = stoi(line);
	LoadedConfig.WindowResolution = Vector2f(XRes, YRes);

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