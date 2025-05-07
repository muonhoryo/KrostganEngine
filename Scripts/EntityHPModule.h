#pragma once

#include <EntityBattleStats.h>
#include <IHitPointModule.h>

namespace KrostganEngine::GameObjects {
	class EntityHPModule:public IHitPointModule {
	public:
		EntityHPModule(EntityBattleStats& BattleStats);

		void TakeDamage(size_t damage) override;
		void Death() override;

	private:
		EntityBattleStats& BattleStats;
	};
}