
#include "ValuesListDeserializer.h"
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>

using namespace KrostganEngine::Core;

ValuesListDeserializer::ValuesListDeserializer() {
	StrValuesArr = vector<ValueDefPair>();
}
ValuesListDeserializer::~ValuesListDeserializer() {
	StrValuesArr.clear();
}

void ValuesListDeserializer::DeserializeValues() {
	string line;
	ifstream st(GetFilePath());
	if (st.bad() == true ||
		st.fail() == true) {
		throw exception("Cannot open file");
	}
	ValueDefPair conf;
	string name;
	string value;
	size_t index;
	char defEndSym = GetValuesDefEndSym();
	if (st.is_open()) {
		while (getline(st, line)) {
			index = line.find(defEndSym);
			name = line.substr(0, index);
			value = line.substr(index + 1, line.length() - index - 1);
			conf = ValueDefPair(name, value);
			StrValuesArr.push_back(conf);
		}
	}
	st.close();
}
bool ValuesListDeserializer::TryGetValue(const string& name, string* value) {
	if (value == nullptr)
		throw exception("Cannot output value");
	value->clear();

	for (auto conf : StrValuesArr) {
		if (conf.Name.find(name) != string::npos) {
			const char* source = conf.Value.c_str();
			char* dest = new char[conf.Value.size()];
			strcpy_s(dest, conf.Value.size() + 1, source);
			&value->append(dest);

			cout << *value << endl;
			return true;
		}
	}
	return false;
}