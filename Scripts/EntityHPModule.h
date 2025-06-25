#pragma once

#include <EntityBattleStats.h>
#include <IAttackableObj.h>
#include <ICallbackRec_Upd.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	
	class HPRegenModule;

	class EntityHPModule:public IHitPointModule {
	public:
		EntityHPModule(IDeathModule& DeathModule, EntityBattleStats& BattleStats)
			:EntityHPModule(DeathModule,BattleStats,nullptr){
		}
		EntityHPModule(IDeathModule& DeathModule, EntityBattleStats& BattleStats, HPRegenModule* RegenModule);
		~EntityHPModule();

		void TakeDamage(AttackInfo attInfo) override;

		const EntityBattleStats& GetStats() const {
			return BattleStats;
		}

	private:
		EntityBattleStats& BattleStats;
		HPRegenModule* RegenModule;
	};

	class HPRegenModule : public ICallbackRec_Upd {

	public:
		virtual ~HPRegenModule(){ }

		void Update(CallbackRecArgs_Upd args) override final {
			if (IsActive) {
				Regen(args);
			}
		}

	protected:
		HPRegenModule(EntityBattleStats& BattleStats)
			:BattleStats(BattleStats){
		}

		virtual void Regen(CallbackRecArgs_Upd& args) = 0;

		EntityBattleStats & BattleStats;
		bool IsActive = true;
	};
}