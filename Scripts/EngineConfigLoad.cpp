
#include <EngineCore.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace KrostganEngine::Core;

EngineConfigLoad::EngineConfigLoad() {
	ConfigArr = vector<ConfigPosition>();
}
EngineConfigLoad::~EngineConfigLoad() {
	ConfigArr.clear();
}

const EngineConfig& EngineConfigLoad::LoadEngineConfig() {
	string line;
	ifstream st(CONFIG_PATH);
	if (st.bad() == true ||
		st.fail() == true) {
		throw exception("Cannot open config file");
	}
	ConfigPosition conf;
	string name;
	string value;
	size_t index;
	if (st.is_open()) {
		while (getline(st, line)) {
			index = line.find(CONFIG_DEF_END_SYM);
			name = line.substr(0, index);
			value = line.substr(index + 1, line.length() - index - 1);
			conf = ConfigPosition(name, value);
			ConfigArr.push_back(conf);
		}
	}
	st.close();
	InitializeConfig();
	ConfigArr.clear();
	return LoadedConfig;
}
void EngineConfigLoad::InitializeConfig() {
	unsigned int XRes;
	unsigned int YRes;
	
	string line = string();
	if (!TryGetConfigValue(EngineConfigsDefsList::X_WINDOW_RESOLUTION, &line))
		throw exception("Cannot parse window's XResolution");
	 XRes= stoi(line);

	if (!TryGetConfigValue(EngineConfigsDefsList::Y_WINDOW_RESOLUTION, &line))
		throw exception("Cannot parse window's YResolution");
	YRes = stoi(line);
	LoadedConfig.WindowResolution = Vector2f(XRes, YRes);
}

bool EngineConfigLoad::TryGetConfigValue(const string& name,string* value) {
	if (value == nullptr)
		throw exception("Cannot output value");
	value->clear();
	
	for (auto conf : ConfigArr) {
		if (conf.Name.find(name) != string::npos) {
			const char *source = conf.Value.c_str();
			char* dest = new char[conf.Value.size()];
			strcpy_s(dest, conf.Value.size()+1, source);
			&value->append(dest);

			cout << *value << endl;
			return true;
		}
	}
	return false;
}

const EngineConfig& EngineConfigLoad::GetLoadedConfig() {
	return LoadedConfig;
}

const string EngineConfigLoad::CONFIG_PATH = "Config.txt";
const char EngineConfigLoad::CONFIG_DEF_END_SYM = ':';