#pragma once

#include <EntityBattleStats.h>
#include <IHitPointModule.h>

namespace KrostganEngine::GameObjects {
	class EntityHPModule:public IHitPointModule {
	public:
		EntityHPModule(EntityBattleStats& BattleStats);

		void TakeDamage(AttackInfo attInfo) override;
		void Death() override;

	private:
		EntityBattleStats& BattleStats;
	};
}