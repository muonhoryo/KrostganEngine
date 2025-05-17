
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Extensions.h>
#include <EngineCore.h>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

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
	size_t size = params->size();
	if (size > 1||
		size == 1 && params[0].size() > 1) {
		units.push_front(*ParseUnitInfo(params));
	}
	params->clear();
	delete params;
	LevelLoadingInfo* levelInfo = new LevelLoadingInfo(units);
	return *levelInfo;
}

UnitLoadInfo* LevelSerialization::ParseUnitInfo(vector<string>* params) {
	if (params->size() == 0)
		throw exception("Missing params of unit");
	vector<string>& paramsRef = *params;
	string* buffer = new string();

	string* name = new string();
	string* sprPath = new string();
	Vector2f sprOffset = Vector2f();
	Vector2f objPosition = Vector2f();
	float objSize;
	Fraction frac;

	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_NAME, name))
		throw exception("Cannot get name of object");
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_SPRITE_PATH, sprPath))
		throw exception("Cannot get path of sprite");
	FStreamExts::ClearPath(sprPath);
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_SPRITE_OFFSET, buffer))
		throw exception("Cannot get offset of sprite");
	sprOffset = ParseVec2f(*buffer);
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_POSITION, buffer))
		throw exception("Caanot get position of object");
	objPosition = ParseVec2f(*buffer);
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::OBJECT_SIZE, buffer))
		throw exception("Cant get size of object");
	objSize = stof(*buffer);
	if (!GetSerValueOfParam(paramsRef, LevelSerializationParDefNames::ENTITY_FRACTION, buffer))
		throw exception("Cannot get fraction of entity");
	FStreamExts::ClearPath(buffer);
	if (FractionsSystem::FractionNames.find(*buffer) == FractionsSystem::FractionNames.end())
		frac = Fraction::Neutral;
	else
		frac = FractionsSystem::FractionNames.at(*buffer);

	//Fill battle stats of unit
	EntityBattleStats& bStats = GetBattleStats(paramsRef, buffer);

	UnitLoadInfo* info = new UnitLoadInfo(*name, *sprPath, sprOffset, objPosition, objSize,bStats,frac);
	delete buffer;
	delete name;
	delete sprPath;
	cout << "Loaded unit:" << endl << "Name: " << info->Name << endl << "Sprite path: " << info->TexturePath <<
		endl << "Sprite offset: " << ToString(info->SpriteOffset) << endl << "Position: " + ToString(info->Position)
		<< endl << "Size: " << info->Size << endl << "Fraction: " << (int)info->EntityFraction << endl;
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

EntityBattleStats& LevelSerialization::GetBattleStats(vector<string>& params, string* buffer) {
	EntityBattleStats& bStats = *new EntityBattleStats();
	float bStat_f;
	size_t bStat_s_t;

	//Moving speed
	if (GetSerValueOfParam(params, LevelSerializationParDefNames::UNIT_MOVINGSPEED, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f >= 0)
			bStats.SetMovingSpeed(bStat_f);
	}				

	//MaxHP
	if (GetSerValueOfParam(params, LevelSerializationParDefNames::ENTITY_MAX_HP, buffer)) {
		bStat_s_t = stoi(*buffer);
		if (bStat_s_t > 0)
			bStats.SetMaxHP(bStat_s_t);
	}

	//CurrentHP
	if (GetSerValueOfParam(params, LevelSerializationParDefNames::ENTITY_CURR_HP, buffer)) {
		bStat_s_t = stoi(*buffer);
		if (bStat_s_t > 0)
			bStats.SetCurrentHP(bStat_s_t);
	}

	//AADamage
	if (GetSerValueOfParam(params, LevelSerializationParDefNames::ENTITY_AA_DAMAGE, buffer)) {
		bStat_s_t = stoi(*buffer);
		bStats.SetAADamage(bStat_s_t);
	}

	//AASpeed
	if (GetSerValueOfParam(params, LevelSerializationParDefNames::ENTITY_AA_SPEED, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f >= 0)
			bStats.SetAASpeed(bStat_f);
	}

	//AARadius
	if (GetSerValueOfParam(params, LevelSerializationParDefNames::ENTITY_AA_RADIUS, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f > 0)
			bStats.SetAARadius(bStat_f);
	}

	//AutoAggrRadius
	if (GetSerValueOfParam(params, LevelSerializationParDefNames::ENTITY_AUTO_AGGRESSIONS_RADIUS, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f > 0)
			bStats.SetAutoAggrRadius(bStat_f);
	}

	return bStats;
}