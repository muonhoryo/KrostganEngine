#pragma once

#include <AttackHitInfo.h>
#include <IAttackableObj.h>
#include <AutoAttackStats.h>
#include <watch_ptr.h>

namespace KrostganEngine::GameObjects {
	struct AutoAttackHitInfo : public AttackHitInfo{

		AutoAttackHitInfo(size_t DealtDmg, watch_ptr_handler_wr<IAttackableObj> Target, const AutoAttackStats& AAStats)
			:AttackHitInfo(DealtDmg),
			Target(Target),
			AAStats(AAStats){}

		watch_ptr_handler_wr<IAttackableObj> Target;
		const AutoAttackStats& AAStats;
	};
}