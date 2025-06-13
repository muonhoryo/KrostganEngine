#pragma once

#include <string>
#include <iostream>

using namespace std;

namespace KrostganEngine::Core {
	struct GlobalConsts {

		float GameObjs_OneSizeSpriteResolution;
		float HeroesSelectArea_OneSizeSpriteResol;
		float UnitsSelectArea_OneSizeSpriteResol;
		float EPS;
		float Orders_CancelTime;
		float EntityAct_RepCoolDown;
		float CameraMovTriggerArea;
		size_t Physics_MaxCollsResolvCount;
		float AAAnim_LineWidth;

		static inline const string DEF_GAMEOBJS_ONESIZE_SPRITERESOL = "GameObjs_OneSizeSpriteResol";
		static inline const string DEF_HEROES_SELECTAREA_ONESIZE_SPRITERESOL = "HeroesSelectArea_OneSizeSpriteResol";
		static inline const string DEF_UNITS_SELECTAREA_ONESIZE_SPRITERESOL = "UnitsSelectArea_OneSizeSpriteResol";
		static inline const string DEF_EPS = "EPS";
		static inline const string DEF_ORDERS_CANCELTIME = "Order_CancelTime";		//In seconds
		static inline const string DEF_ENTITY_ACTION_REPEAT_COOLDOWN = "EntityAct_RepCoolDown";		//In seconds
		static inline const string DEF_CAMERA_MOVING_TRIGGER_AREA = "CameraMovTriggerArea";
		static inline const string DEF_PHYSICS_MAX_COLLISION_RESOLVE_COUNT = "Physics_MaxCollsResolvCount";
		static inline const string DEF_AA_ANIM_LINE_WIDTH = "AAAnim_LineWidth";
	};
}