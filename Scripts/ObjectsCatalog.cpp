
#include <ObjectsCatalog.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <Extensions.h>
#include <EngineCore.h>
#include <EntityBattleStats.h>
#include <RelationsSystem.h>

using namespace KrostganEngine::Core;

void ObjsCatalogDeserial::DeserializeCatalog(string serPath) {

	string line;
	ifstream st(serPath);
	if (st.bad() == true ||
		st.fail() == true)
		throw exception("Cannot open level file");

	ObjectsCatalog::Unload();

	vector<string>& params = *new vector<string>();
	if (st.is_open()) {
		while (getline(st, line)) {

			if (line.find(OBJECTS_SEP_LINE) != string::npos) {

				ObjectsCatalog::Add(&ParseObjInfo(params));
				params.clear();
			}
			else {

				params.push_back(line);
			}
		}
	}
	st.close();
	size_t size = params.size();
	if (size > 1 ||
		size == 1 && params[0].size() > 1) {

		ObjectsCatalog::Add(&ParseObjInfo(params));
	}
	params.clear();
	delete& params;
}

//GameObject* ObjsCatalogDeserial::DeserializeObj(vector<string>& params,LevelLoadingInfo& levelInfo, Vector2f position) {
//
//	return ParseObjInfo(params).InstanceObject(levelInfo,position);
//}

GameObjectLoadInfo& ObjsCatalogDeserial::ParseObjInfo(vector<string>& params) {

	string* output = new string();
	if (TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_TYPE, output))
	{
		if (output->find(SerializationObjectsTypes::OBJECT_TYPE_UNIT) != string::npos) {

			return ParseUnitInfo(params);
		}
		else if (output->find(SerializationObjectsTypes::OBJECT_TYPE_HERO) != string::npos) {

			return ParseHeroInfo(params);
		}
		else if (output->find(SerializationObjectsTypes::OBJECT_TYPE_WALL)!=string::npos) {

			return ParseWallInfo(params);
		}
	}
	throw exception("Cant parse info: missing type");
}
UnitLoadInfo& ObjsCatalogDeserial::ParseUnitInfo(vector<string>& params) {
	if (params.size() == 0)
		throw exception("Missing params of unit");
	UnitLoadInfo& info = *new UnitLoadInfo();
	string* buffer = new string();

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_NAME, buffer))
		throw exception("Cannot get name of object");
	info.Name = *buffer;

	if (TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_CATALOG_ID, buffer)) {
		info.CatalogID = stoi(*buffer);
	}

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_SPRITE_SOURCE, buffer))
		throw exception("Cannot get path of sprite");
	FStreamExts::ClearPath(buffer);
	info.SpriteSource= *buffer;

	if (TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_POSITION, buffer)) {

		info.Position = ParseVec2f(*buffer);
	}

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_SIZE, buffer))
		throw exception("Cant get size of object");
	info.Size = stof(*buffer);

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_FRACTION, buffer))
		throw exception("Cannot get fraction of entity");
	FStreamExts::ClearPath(buffer);
	if (FractionsSystem::FractionNames.find(*buffer) == FractionsSystem::FractionNames.end())
		info.EntityFraction = Fraction::Neutral;
	else
		info.EntityFraction = FractionsSystem::FractionNames.at(*buffer);

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_HPBAR_SPRITE_SOURCE, buffer))
		throw exception("Cant get hpbar sprite");
	FStreamExts::ClearPath(buffer);
	info.HPBarSpriteSource = *buffer;

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_HPBAR_MASK, buffer))
		throw exception("Cant get hpbar mask");
	FStreamExts::ClearPath(buffer);
	info.HPBarMaskSource = *buffer;

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_SELECT_AREA_SOURCE, buffer))
		throw exception("Cant get selection area");
	FStreamExts::ClearPath(buffer);
	info.SelectionAreaSource = *buffer;

	//Fill battle stats of unit
	EntityBattleStats& bStats = GetBattleStats(params, buffer);

	info.BattleStats = &bStats;

	delete buffer;

	cout << "Loaded unit:" << endl << "Name: " << info.Name << endl << "Sprite: " << info.SpriteSource<<
		endl << "Size: " << info.Size << endl << "Fraction: " << (int)info.EntityFraction << endl;
	return info;
}
HeroLoadInfo& ObjsCatalogDeserial::ParseHeroInfo(vector<string>& params) {

	UnitLoadInfo& info = ParseUnitInfo(params);

	HeroLoadInfo& heInfo = *new HeroLoadInfo(*(HeroLoadInfo*)&info);
	delete &info;
	return  heInfo;
}
WallLoadInfo& ObjsCatalogDeserial::ParseWallInfo(vector<string>& params) {

	if (params.size() == 0)
		throw exception("Missing params of unit");
	string* buffer = new string();
	WallLoadInfo& info = *new WallLoadInfo();

	if (TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_CATALOG_ID, buffer)) {
		info.CatalogID = stoi(*buffer);
	}

	if (TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_POSITION, buffer)) {

		info.Position = ParseVec2f(*buffer);
	}

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_NAME, buffer))
		throw exception("Cannot get name of object");
	info.Name = *buffer;

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_SPRITE_SOURCE, buffer))
		throw exception("Cannot get source of sprite");
	FStreamExts::ClearPath(buffer);
	info.SpriteSource= *buffer;

	if (!TryGetSerValueOfParam(params, SerializationParDefNames::OBJECT_SIZE, buffer))
		throw exception("Cant get size of object");
	info.Size = stof(*buffer);

	delete buffer;

	cout << "Loaded wall: " << endl << "Name: " << info.Name << endl << "Sprite path: " << info.SpriteSource<<
		endl << "Size: " << info.Size << endl;
	return info;
}

bool ObjsCatalogDeserial::TryGetSerValueOfParam(vector<string>& params, const string& paramName, string* output) {
	(*output).clear();
	for (auto& par : params) {
		if (par.find(paramName) != string::npos) {
			size_t index = par.find(PAR_DEF_NAME_END_SYM);
			if (index == string::npos)
				throw exception("Incorrect parameter format");
			(*output).append(par.begin() + index + 1, par.end());
			return true;
		}
	}
	return false;
}

EntityBattleStats& ObjsCatalogDeserial::GetBattleStats(vector<string>& params, string* buffer) {
	EntityBattleStats& bStats = *new EntityBattleStats();
	float bStat_f;
	size_t bStat_s_t;

	//Moving speed
	if (TryGetSerValueOfParam(params, SerializationParDefNames::UNIT_MOVINGSPEED, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f >= 0)
			bStats.SetMovingSpeed(bStat_f);
	}

	//MaxHP
	if (TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_MAX_HP, buffer)) {
		bStat_s_t = stoi(*buffer);
		if (bStat_s_t > 0)
			bStats.SetMaxHP(bStat_s_t);
	}

	//HPRegenAmount
	if (TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_REGEN_HP_COUNT, buffer)) {
		bStat_s_t = stoi(*buffer);
		bStats.SetHPRegenAmount(bStat_s_t);
	}

	//HPRegenTick
	if (TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_REGEN_HP_TICK, buffer)) {
		bStat_f = stof(*buffer);
		bStats.SetHPRegenTick(bStat_f);
	}

	//AADamage
	if (TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_AA_DAMAGE, buffer)) {
		bStat_s_t = stoi(*buffer);
		bStats.SetAADamage(bStat_s_t);
	}

	//AASpeed
	if (TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_AA_SPEED, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f >= 0)
			bStats.SetAASpeed(bStat_f);
	}

	//AARadius
	if (TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_AA_RADIUS, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f > 0)
			bStats.SetAARadius(bStat_f);
	}

	//AutoAggrRadius
	if (TryGetSerValueOfParam(params, SerializationParDefNames::ENTITY_AUTO_AGGR_RADIUS, buffer)) {
		bStat_f = stof(*buffer);
		if (bStat_f > 0)
			bStats.SetAutoAggrRadius(bStat_f);
	}

	return bStats;
}