#pragma once

#include <IAttackableObj.h>
#include <AutoAttackStats.h>
#include <watch_ptr.h>

using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {
	struct AutoAttackHitInfo : public AttackHitInfo{

		AutoAttackHitInfo
			(size_t DealtDmg, 
			watch_ptr_handler_wr<IAttackableObj> Target, 
			const AutoAttackStats& AAStats,
			Fraction DmgDealerFrac)
				:AttackHitInfo(DealtDmg, Target, DmgDealerFrac),
				AAStats(AAStats){}

		const AutoAttackStats& AAStats;
	};
}