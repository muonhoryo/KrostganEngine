
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Extensions.h>
#include <EngineCore.h>
#include <EntityBattleStats.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

LevelLoadingInfo& LevelSerialization::DeserializeLevel(string serPath) {
	auto& consts = Engine::GetGlobalConsts();
	float i = consts.GameObjs_OneSizeSpriteResolution;
	string line;
	ifstream st(serPath);
	if (st.bad() == true ||
		st.fail() == true)
		throw exception("Cannot open level file");
	forward_list<UnitLoadInfo>& units = *new forward_list<UnitLoadInfo>();

	vector<string>* params = new vector<string>();
	if (st.is_open()) {
		while (getline(st, line)) {
			if (line.find(OBJECTS_SEP_LINE)!=string::npos) {
				units.push_front(*ParseUnitInfo(params));
				params->clear();
			}
			else {
				params->push_back(line);
			}
		}
	}
	st.close();
	units.push_front(*ParseUnitInfo(params));
	params->clear();
	delete params;
	LevelLoadingInfo* levelInfo = new LevelLoadingInfo(units);
	return *levelInfo;
}

UnitLoadInfo* LevelSerialization::ParseUnitInfo(vector<string>* params) {
	if (params->size() == 0)
		throw exception("Missing params of unit");
	vector<string>& paramsRef = *params;
	string* name = new string();
	string* sprPath = new string();
	string* serValue = new string();
	Vector2f sprOffset = Vector2f();
	Vector2f objPosition = Vector2f();
	float objSize;
	float bStas_f;
	EntityBattleStats& bStats = *new EntityBattleStats();

	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_NAME, name))
		throw exception("Cannot get name of object");
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_SPRITE_PATH, sprPath))
		throw exception("Cannot get path of sprite");
	FStreamExts::ClearPath(sprPath);
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_SPRITE_OFFSET, serValue))
		throw exception("Cannot get offset of sprite");
	sprOffset = VectExts::ParseVec2f(*serValue);
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_POSITION, serValue))
		throw exception("Caanot get position of object");
	objPosition = VectExts::ParseVec2f(*serValue);
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_SIZE, serValue))
		throw exception("Cant get size of object");
	objSize = stof(*serValue);
	//Fill battle stats of unit
	if (GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::UNIT_MOVINGSPEED, serValue)) {
		bStas_f = stof(*serValue);
		if (bStas_f >= 0)
			bStats.SetMovingSpeed(bStas_f);
	}

	UnitLoadInfo* info = new UnitLoadInfo(*name, *sprPath, sprOffset, objPosition, objSize,bStats);
	delete serValue;
	delete name;
	delete sprPath;
	cout << "Loaded unit:" << endl << "Name: " << info->Name << endl << "Sprite path: " << info->TexturePath <<
		endl << "Sprite offset: " << VectExts::ToString(info->SpriteOffset) << endl << "Position: " + VectExts::ToString(info->Position) 
		<< endl<<"Size: "<<info->Size<<endl;
	return info;
}

bool LevelSerialization::GetSerValueOfParam(vector<string>& params, const string& paramName,string* output) {
	(*output).clear();
	for (auto par : params) {
		if (par.find(paramName) != string::npos) {
			size_t index = par.find(LevelSerialization::PAR_DEF_NAME_END_SYM);
			if (index == string::npos)
				throw exception("Incorrect parameter format");
			(*output).append(par.begin() + index+1, par.end());
			return true;
		}
	}
	return false;
}