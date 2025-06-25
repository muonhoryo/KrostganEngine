
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
	forward_list<UnitLoadInfo*>& units = *new forward_list<UnitLoadInfo*>();
	forward_list<WallLoadInfo*>& walls = *new forward_list<WallLoadInfo*>();
	forward_list<HeroLoadInfo*>& heroes = *new forward_list<HeroLoadInfo*>();
	LevelLoadingInfo& levelInfo = *new LevelLoadingInfo(units,heroes,walls);

	vector<string>& params = *new vector<string>();
	if (st.is_open()) {
		while (getline(st, line)) {
			if (line.find(OBJECTS_SEP_LINE)!=string::npos) {

				ParseObjInfo(params, levelInfo);
				params.clear();
			}
			else {
				params.push_back(line);
			}
		}
	}
	st.close();
	size_t size = params.size();
	if (size > 1||
		size == 1 && params[0].size() > 1) {

		ParseObjInfo(params, levelInfo);
	}
	params.clear();
	delete &params;
	return levelInfo;
}

void LevelSerialization::ParseObjInfo(vector<string>& params, LevelLoadingInfo& levelInfo) {

	string* output = new string();
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_TYPE, output))
	{
		if (output->find(LevelSerObjectsTypes::OBJECT_TYPE_UNIT)!=string::npos) {

			levelInfo.Units.push_front(&ParseUnitInfo(params));
		}
		else if (output->find(LevelSerObjectsTypes::OBJECT_TYPE_HERO) != string::npos) {

			levelInfo.Heroes.push_front(&ParseHeroInfo(params));
		}
		else if (output->find(LevelSerObjectsTypes::OBJECT_TYPE_WALL)) {
			
			levelInfo.Walls.push_front(&ParseWallInfo(params));
		}
	}
}
UnitLoadInfo& LevelSerialization::ParseUnitInfo(vector<string>& params) {
	if (params.size() == 0)
		throw exception("Missing params of unit");
	UnitLoadInfo& info = *new UnitLoadInfo();
	string* buffer = new string();

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_NAME, buffer))
		throw exception("Cannot get name of object");
	info.Name = *buffer;

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_SPRITE_PATH, buffer))
		throw exception("Cannot get path of sprite");
	FStreamExts::ClearPath(buffer);
	info.TexturePath = *buffer;

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_SPRITE_OFFSET, buffer))
		throw exception("Cannot get offset of sprite");
	info.SpriteOffset = ParseVec2f(*buffer);

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_POSITION, buffer))
		throw exception("Caanot get position of object");
	info.Position = ParseVec2f(*buffer);

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_SIZE, buffer))
		throw exception("Cant get size of object");
	info.Size = stof(*buffer);

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_FRACTION, buffer))
		throw exception("Cannot get fraction of entity");
	FStreamExts::ClearPath(buffer);
	if (FractionsSystem::FractionNames.find(*buffer) == FractionsSystem::FractionNames.end())
		info.EntityFraction = Fraction::Neutral;
	else
		info.EntityFraction = FractionsSystem::FractionNames.at(*buffer);

	//Fill battle stats of unit
	EntityBattleStats& bStats = GetBattleStats(params, buffer);

	info.BattleStats = &bStats;

	delete buffer;

	cout << "Loaded unit:" << endl << "Name: " << info.Name << endl << "Sprite path: " << info.TexturePath <<
		endl << "Sprite offset: " << ToString(info.SpriteOffset) << endl << "Position: " + ToString(info.Position)
		<< endl << "Size: " << info.Size << endl << "Fraction: " << (int)info.EntityFraction << endl;
	return info;
}
HeroLoadInfo& LevelSerialization::ParseHeroInfo(vector<string>& params) {

	return (HeroLoadInfo&)ParseUnitInfo(params);
}
WallLoadInfo& LevelSerialization::ParseWallInfo(vector<string>& params) {

	if (params.size() == 0)
		throw exception("Missing params of unit");
	string* buffer = new string();
	WallLoadInfo& info = *new WallLoadInfo();

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_NAME, buffer))
		throw exception("Cannot get name of object");
	info.Name = *buffer;

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_SPRITE_PATH, buffer))
		throw exception("Cannot get path of sprite");
	FStreamExts::ClearPath(buffer);
	info.TexturePath = *buffer;

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_SPRITE_OFFSET, buffer))
		throw exception("Cannot get offset of sprite");
	info.SpriteOffset = ParseVec2f(*buffer);

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_POSITION, buffer))
		throw exception("Caanot get position of object");
	info.Position = ParseVec2f(*buffer);

	if (!TryGetSerValueOfParam(params, LevelSerParDefNames::OBJECT_SIZE, buffer))
		throw exception("Cant get size of object");
	info.Size = stof(*buffer);

	delete buffer;

	cout << "Loaded wall: "<< endl << "Name: " << info.Name << endl << "Sprite path: " << info.TexturePath <<
		endl << "Sprite offset: " << ToString(info.SpriteOffset) << endl << "Position: " + ToString(info.Position)
		<< endl << "Size: " << info.Size << endl;
	return info;
}

bool LevelSerialization::TryGetSerValueOfParam(vector<string>& params, const string& paramName,string* output) {
	(*output).clear();
	for (auto& par : params) {
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
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::UNIT_MOVINGSPEED, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f >= 0)
			bStats.SetMovingSpeed(bStat_f);
	}				

	//MaxHP
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_MAX_HP, buffer)) {
		bStat_s_t = stoi(*buffer);
		if (bStat_s_t > 0)
			bStats.SetMaxHP(bStat_s_t);
	}

	//CurrentHP
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_CURR_HP, buffer)) {
		bStat_s_t = stoi(*buffer);
		if (bStat_s_t > 0)
			bStats.SetCurrentHP(bStat_s_t);
	}

	//HPRegenAmount
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_REGEN_HP_COUNT, buffer)) {
		bStat_s_t = stoi(*buffer);
		bStats.SetHPRegenAmount(bStat_s_t);
	}

	//HPRegenTick
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_REGEN_HP_TICK, buffer)) {
		bStat_f = stof(*buffer);
		bStats.SetHPRegenTick(bStat_f);
	}

	//AADamage
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_AA_DAMAGE, buffer)) {
		bStat_s_t = stoi(*buffer);
		bStats.SetAADamage(bStat_s_t);
	}

	//AASpeed
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_AA_SPEED, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f >= 0)
			bStats.SetAASpeed(bStat_f);
	}

	//AARadius
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_AA_RADIUS, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f > 0)
			bStats.SetAARadius(bStat_f);
	}

	//AutoAggrRadius
	if (TryGetSerValueOfParam(params, LevelSerParDefNames::ENTITY_AUTO_AGGRESSIONS_RADIUS, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f > 0)
			bStats.SetAutoAggrRadius(bStat_f);
	}

	return bStats;
}