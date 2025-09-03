
#include <ValuesListDeserializer.h>
#include <string>
#include <string.h>
#include <fstream>
#include <iostream>
#include <VectExts.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine;

ValuesListDeserializer::ValuesListDeserializer() {
	StrValuesArr = vector<ValueDefPair*>();
}
ValuesListDeserializer::~ValuesListDeserializer() {
	StrValuesArr.clear();
}

void ValuesListDeserializer::DeserializeValues() {

	StrValuesArr.clear();

	string line;
	ifstream st(GetFilePath());
	if (st.bad() == true ||
		st.fail() == true) {
		throw exception("Cannot open file");
	}
	ValueDefPair* conf;
	string name;
	string value;
	size_t index;
	char defEndSym = GetValuesDefEndSym();
	if (st.is_open()) {
		while (getline(st, line)) {
			index = line.find(defEndSym);
			name = line.substr(0, index);
			value = line.substr(index + 1, line.length() - index - 1);
			conf = new ValueDefPair(name, value);
			StrValuesArr.push_back(conf);
		}
	}
	st.close();
}
void ValuesListDeserializer::DeserializeValues(vector<string>& serValues) {

	StrValuesArr.clear();

	ValueDefPair* conf;
	string name;
	string value;
	size_t index;
	char defEndSym = GetValuesDefEndSym();
	for (auto& line : serValues) {
		index = line.find(defEndSym);
		name = line.substr(0, index);
		value = line.substr(index + 1, line.length() - index - 1);
		conf = new ValueDefPair(name, value);
		StrValuesArr.push_back(conf);
	}
}
bool ValuesListDeserializer::TryGetValue(const string& definition, string& value) {
	
	value.clear();

	for (auto conf : StrValuesArr) {
		if (conf->Name.find(definition) != string::npos) {
			const char* source = conf->Value.c_str();
			char* dest = new char[conf->Value.size()];
			strcpy_s(dest, conf->Value.size() + 1, source);
			value.append(dest);

			cout << value << endl;
			return true;
		}
	}
	return false;
}
void ValuesListDeserializer::GetValueByDef(const string& definition, string& buffer) {

	if (!TryGetValue(definition, buffer)) {
		string std = "Missing value of " + definition;
		throw exception(std.c_str());
	}
}
float ValuesListDeserializer::DeserValueByDef_float(const string& definition, string& value) {
	
	GetValueByDef(definition, value);
	float res = stof(value);
	return res;
}
int	ValuesListDeserializer::DeserValueByDef_int(const string& definition, string& value) {

	GetValueByDef(definition, value);
	int res = stoi(value);
	return res;
}
unsigned int ValuesListDeserializer::DeserValueByDef_uint(const string& definition, string& value) {

	GetValueByDef(definition, value);
	unsigned int res = stol(value);
	return res;
}
size_t ValuesListDeserializer::DeserValueByDef_size_t(const string& definition, string& value) {

	GetValueByDef(definition, value);
	size_t res = stoull(value);
	return res;
}
Vector2u ValuesListDeserializer::DeserValueByDef_Vec2u(const string& definition, string& value) {

	GetValueByDef(definition, value);
	Vector2u res = ParseVec2u(value);
	return res;
}
Vector2f ValuesListDeserializer::DeserValueByDef_Vec2f(const string& definition, string& value) {

	GetValueByDef(definition, value);
	Vector2f res = ParseVec2f(value);
	return res;

}

bool ValuesListDeserializer::CouldBeName(const string& value) {

	return value.find('/')==string::npos &&
		value.find('\\')==string::npos &&
		value.find('.') == string::npos;
		
}