
#include <EngineCore.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
using namespace KrostganEngine::Core;

GameConfigLoad::GameConfigLoad() {
	string line;
	ifstream st(CONFIG_PATH);
	if (st.bad()==true||
		st.fail()==true)
		throw exception("Cannot open config file");
	ConfigPosition conf;
	string name;
	string value;
	size_t index;
	if (st.is_open()) {
		while (getline(st, line)) {
			index = line.find(CONFIG_SEP_SYM);
			name = line.substr(0, index);
			value = line.substr(index + 1, line.length() - index - 1);
			conf = ConfigPosition(name, value);
			this->ConfigArr.push_back(conf);
		}
	}
	st.close();
}
GameConfigLoad::~GameConfigLoad() {
	ConfigArr.clear();
}
bool GameConfigLoad::GetConfigValue(const string& name,string* value) {
	if (value == nullptr)
		throw exception("Cannot output value");
	value->clear();
	
	for (auto conf : ConfigArr) {
		if (conf.Name.find(name) != string::npos) {
			const char *source = conf.Value.c_str();
			char dest[sizeof(source)];
			strcpy_s(dest, sizeof(dest), source);
			&value->append(dest);

			cout << *value << endl;
			return true;
		}
	}
	return false;
}

const string GameConfigLoad::CONFIG_PATH = "Config.txt";
const char GameConfigLoad::CONFIG_SEP_SYM = ':';