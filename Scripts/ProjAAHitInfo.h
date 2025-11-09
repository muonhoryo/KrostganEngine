#pragma once

#include <AutoAttackStats.h>
#include <CachedBattleStats.h>

using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {
	struct ProjAAHitInfo : public AttackHitInfo {

		ProjAAHitInfo
			(size_t												DealtDmg, 
			watch_ptr_handler_wr<IAttackableObj>				Target,
			const CachedBattleStats
				<AutoAttackStats_Consts::FIELDS_COUNT_S_T, 
				AutoAttackStats_Consts::FIELDS_COUNT_F, 
				AutoAttackStats_Consts::FIELDS_COUNT_BOOL> &	CachedAAStats,
			Fraction DmgDealerFrac)
					:AttackHitInfo(DealtDmg,Target, DmgDealerFrac),
					CachedAAStats(CachedAAStats)
		{}

		const CachedBattleStats
			<AutoAttackStats_Consts::FIELDS_COUNT_S_T,
			AutoAttackStats_Consts::FIELDS_COUNT_F,
			AutoAttackStats_Consts::FIELDS_COUNT_BOOL>& CachedAAStats;
	};
}