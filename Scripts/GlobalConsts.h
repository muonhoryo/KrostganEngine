#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace KrostganEngine::Core {
	struct GlobalConsts {

		float GameObjs_OneSizeSpriteResolution;
		float EPS;
		float Orders_CancelTime;
		float EntityAct_RepCoolDown;
		float CameraMovTriggerArea;
		size_t Physics_MaxCollsResolvCount;
		float AAAnim_LineWidth;
		float AverageLifeTime_DeathEffect;
		float LoseMsg_AppearingTime;
		float LoseMsg_ShowingTime;
		float LoseMsg_TransitTime;
		float Units_MovingAbilityCheckTick;
		float Units_ImmobilityCheckValue;
		float EscapeBtn_PressDelay;

		static inline const string DEF_GAMEOBJS_ONESIZE_SPRITERESOL = "GameObjs_OneSizeSpriteResol";
		static inline const string DEF_EPS = "EPS";
		static inline const string DEF_ORDERS_CANCELTIME = "Order_CancelTime";		//In seconds
		static inline const string DEF_ENTITY_ACTION_REPEAT_COOLDOWN = "EntityAct_RepCoolDown";		//In seconds
		static inline const string DEF_CAMERA_MOVING_TRIGGER_AREA = "CameraMovTriggerArea";
		static inline const string DEF_PHYSICS_MAX_COLLISION_RESOLVE_COUNT = "Physics_MaxCollsResolvCount";
		static inline const string DEF_AA_ANIM_LINE_WIDTH = "AAAnim_LineWidth";
		static inline const string DEF_AVERGAE_LIFETIME_DEATHEFFECT = "AverageLifeTime_DeathEffect";	//In seconds
		static inline const string DEF_LOSEMESSAG_APPEARING_TIME = "LoseMsg_AppearingTime";		//In seconds
		static inline const string DEF_LOSEMESSAG_SHOWING_TIME = "LoseMsg_ShowingTime";		//In seconds
		static inline const string DEF_LOSEMESSAG_TRANSIT_TIME = "LoseMsg_TransitTime";		//In seconds
		static inline const string DEF_UNITS_MOVING_ABILITY_CHECK_TICK = "Units_MovingAbilityCheckTick";		//In seconds
		static inline const string DEF_UNITS_IMMOBILITY_CHECK_VALUE = "Units_ImmobilityCheckValue";		//In seconds
		static inline const string DEF_ESCAPE_BTN_PRESS_DELAY = "EscapeBtn_PressDelay";		//In seconds
	};
}