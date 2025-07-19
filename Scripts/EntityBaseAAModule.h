#pragma once

#include <AutoAttackModule.h>
#include <EntityBattleStats.h>
#include <TransformableObj.h>

namespace KrostganEngine::GameObjects {
	class EntityBaseAAModule:public AutoAttackModule {
	public:
		EntityBaseAAModule(EntityBattleStats& BattleStats,TransformableObj& Owner);

		void SetAsTarget(watch_ptr_handler_wr<IAttackableObj>* target) override;
		bool CheckTargetReach() override;
		bool CheckTargetReach(const IAttackableObj& potentTarget) override;
		bool TryDealDamageToTarget() override;

	private:
		EntityBattleStats& BattleStats;
		TransformableObj& Owner;
	};
}