#pragma once

#include <AttackInfo.h>
#include <IAttackableObj.h>

namespace KrostganEngine::GameObjects {
	struct AutoAttackInfo : public AttackInfo{

		AutoAttackInfo(size_t DealtDmg, IAttackableObj& Target, float AASpeed)
			:AttackInfo(DealtDmg),
			Target(Target),
			AASpeed(AASpeed){}

		IAttackableObj& Target;
		float AASpeed;
	};
}