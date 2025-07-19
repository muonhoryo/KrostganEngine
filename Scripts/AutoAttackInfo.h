#pragma once

#include <AttackInfo.h>
#include <IAttackableObj.h>
#include <watch_ptr.h>

namespace KrostganEngine::GameObjects {
	struct AutoAttackInfo : public AttackInfo{

		AutoAttackInfo(size_t DealtDmg, watch_ptr_handler_wr<IAttackableObj> Target, float AASpeed)
			:AttackInfo(DealtDmg),
			Target(Target),
			AASpeed(AASpeed){}

		watch_ptr_handler_wr<IAttackableObj> Target;
		float AASpeed;
	};
}