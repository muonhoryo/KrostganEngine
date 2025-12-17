
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

	LoadedGlobalConsts.Instantiation_MaxDepthLvl = DeserValueByDef_int(GlobalConsts::DEF_INSTANTIATION_MAXDEPTHLVL, line);

	LoadedGlobalConsts.Physics_MaxCollsResolvCount = DeserValueByDef_size_t(GlobalConsts::DEF_PHYSICS_MAX_COLLISION_RESOLVE_COUNT, line);
	LoadedGlobalConsts.WarFogObserversManager_CacheSize = DeserValueByDef_size_t(GlobalConsts::DEF_WARFOG_OBSRMANAGER_CACHE_SIZE, line);

	LoadedGlobalConsts.GameObjs_OneSizeSpriteResolution = DeserValueByDef_float(GlobalConsts::DEF_GAMEOBJS_ONESIZE_SPRITERESOL, line);
	LoadedGlobalConsts.EPS = DeserValueByDef_float(GlobalConsts::DEF_EPS, line);
	LoadedGlobalConsts.Orders_CancelTime = DeserValueByDef_float(GlobalConsts::DEF_ORDERS_CANCELTIME, line);
	LoadedGlobalConsts.EntityAct_RepCoolDown = DeserValueByDef_float(GlobalConsts::DEF_ENTITY_ACTION_REPEAT_COOLDOWN, line);
	LoadedGlobalConsts.CameraMovTriggerArea = DeserValueByDef_float(GlobalConsts::DEF_CAMERA_MOVING_TRIGGER_AREA, line);
	LoadedGlobalConsts.AAAnim_LineWidth = DeserValueByDef_float(GlobalConsts::DEF_AA_ANIM_LINE_WIDTH, line);
	LoadedGlobalConsts.AverageLifeTime_DeathEffect = DeserValueByDef_float(GlobalConsts::DEF_AVERGAE_LIFETIME_DEATHEFFECT, line);
	LoadedGlobalConsts.LoseMsg_AppearingTime = DeserValueByDef_float(GlobalConsts::DEF_LOSEMESSAG_APPEARING_TIME, line);
	LoadedGlobalConsts.Units_ImmobilityCheckValue = DeserValueByDef_float(GlobalConsts::DEF_UNITS_IMMOBILITY_CHECK_VALUE, line);
	LoadedGlobalConsts.LoseMsg_ShowingTime = DeserValueByDef_float(GlobalConsts::DEF_LOSEMESSAG_SHOWING_TIME, line);
	LoadedGlobalConsts.LoseMsg_TransitTime = DeserValueByDef_float(GlobalConsts::DEF_LOSEMESSAG_TRANSIT_TIME, line);
	LoadedGlobalConsts.Units_MovingAbilityCheckTick = DeserValueByDef_float(GlobalConsts::DEF_UNITS_MOVING_ABILITY_CHECK_TICK, line);
	LoadedGlobalConsts.EscapeBtn_PressDelay = DeserValueByDef_float(GlobalConsts::DEF_ESCAPE_BTN_PRESS_DELAY, line);
	LoadedGlobalConsts.TakeDmg_FadeTime = DeserValueByDef_float(GlobalConsts::DEF_TAKEDMG_FADETIME, line);
	LoadedGlobalConsts.AutoAggrModule_CheckTick = DeserValueByDef_float(GlobalConsts::DEF_AUTOAGGR_CHECKTICK, line);
	LoadedGlobalConsts.WarFogObserversManager_PosHashCellSize = DeserValueByDef_float(GlobalConsts::DEF_WARFOG_OBSRMANAGER_POSHASHCELLSIZE, line);

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