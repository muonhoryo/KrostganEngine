
#include <EngineCore.h>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;
using namespace KrostganEngine::Core;

GlobalConstsLoad::GlobalConstsLoad() :ValuesListDeserializer(), LoadedGlobalConsts(*new GlobalConsts()) {
}

const GlobalConsts& GlobalConstsLoad::LoadGlobalConsts() {
	DeserializeValues();

	string line = string();
	LoadedGlobalConsts.GameObjs_OneSizeSpriteResolution = DeserializeValueByDefinition(GlobalConsts::DEF_GAMEOBJS_ONESIZE_SPRITERESOL, &line);
	LoadedGlobalConsts.HeroesSelectArea_OneSizeSpriteResol = DeserializeValueByDefinition(GlobalConsts::DEF_HEROES_SELECTAREA_ONESIZE_SPRITERESOL, &line);
	LoadedGlobalConsts.UnitsSelectArea_OneSizeSpriteResol = DeserializeValueByDefinition(GlobalConsts::DEF_UNITS_SELECTAREA_ONESIZE_SPRITERESOL, &line);
	LoadedGlobalConsts.EPS = DeserializeValueByDefinition(GlobalConsts::DEF_EPS, &line);
	LoadedGlobalConsts.Orders_CancelTime = DeserializeValueByDefinition(GlobalConsts::DEF_ORDERS_CANCELTIME, &line);
	LoadedGlobalConsts.EntityAct_RepCoolDown = DeserializeValueByDefinition(GlobalConsts::DEF_ENTITY_ACTION_REPEAT_COOLDOWN, &line);
	LoadedGlobalConsts.CameraMovTriggerArea = DeserializeValueByDefinition(GlobalConsts::DEF_CAMERA_MOVING_TRIGGER_AREA, &line);
	LoadedGlobalConsts.Physics_MaxCollsResolvCount = DeserializeValueByDefinition(GlobalConsts::DEF_PHYSICS_MAX_COLLISION_RESOLVE_COUNT, &line);
	LoadedGlobalConsts.AAAnim_LineWidth = DeserializeValueByDefinition(GlobalConsts::DEF_AA_ANIM_LINE_WIDTH, &line);
	LoadedGlobalConsts.AverageLifeTime_DeathEffect = DeserializeValueByDefinition(GlobalConsts::DEF_AVERGAE_LIFETIME_DEATHEFFECT, &line);
	LoadedGlobalConsts.LoseMsg_AppearingTime = DeserializeValueByDefinition(GlobalConsts::DEF_LOSEMESSAG_APPEARING_TIME, &line);
	LoadedGlobalConsts.Units_ImmobilityCheckValue = DeserializeValueByDefinition(GlobalConsts::DEF_UNITS_IMMOBILITY_CHECK_VALUE, &line);
	LoadedGlobalConsts.LoseMsg_ShowingTime = DeserializeValueByDefinition(GlobalConsts::DEF_LOSEMESSAG_SHOWING_TIME, &line);
	LoadedGlobalConsts.LoseMsg_TransitTime = DeserializeValueByDefinition(GlobalConsts::DEF_LOSEMESSAG_TRANSIT_TIME, &line);
	LoadedGlobalConsts.Units_MovingAbilityCheckTick = DeserializeValueByDefinition(GlobalConsts::DEF_UNITS_MOVING_ABILITY_CHECK_TICK, &line);

	StrValuesArr.clear();
	return LoadedGlobalConsts;
}
const GlobalConsts& GlobalConstsLoad::GetLoadedConsts() {
	return LoadedGlobalConsts;
}

const string GlobalConstsLoad::GetFilePath() {
	return CONSTS_PATH;
}
const char GlobalConstsLoad::GetValuesDefEndSym() {
	return CONFIG_DEF_END_SYM;
}

float GlobalConstsLoad::DeserializeValueByDefinition(const string& definition, string* buffer) {
	if (!TryGetValue(definition, buffer)) {
		string str = "Missing value of " + definition;
		throw exception(str.c_str());
	}
	float res = stof(*buffer);
	return res;
}

const string GlobalConstsLoad::CONSTS_PATH = "GlobalConsts.txt";
const char GlobalConstsLoad::CONFIG_DEF_END_SYM = ':';