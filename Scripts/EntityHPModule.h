#pragma once

#include <EntityBattleStats.h>
#include <IAttackableObj.h>

namespace KrostganEngine::GameObjects {
	class EntityHPModule:public IHitPointModule {
	public:
		EntityHPModule(IDeathModule& DeathModule,EntityBattleStats& BattleStats);

		void TakeDamage(AttackInfo attInfo) override;

	private:
		EntityBattleStats& BattleStats;
	};
}