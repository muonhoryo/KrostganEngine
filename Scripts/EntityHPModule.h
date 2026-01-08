#pragma once

#include <EntityBattleStats.h>
#include <IAttackableObj.h>
#include <ICallbackRec_Upd.h>
#include <IndicatorFill.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {
	
	class HPRegenModule;

	class EntityHPModule:public IHitPointModule {
	public:
		EntityHPModule(
			IDeathModule&		DeathModule, 
			EntityBattleStats&	BattleStats,
			IndicatorFill&		HPBar,
			TakeDamageAnimation& TakeDmgAnim);

		virtual ~EntityHPModule();

		size_t	TakeDamage_Action	(const AttackHitInfo& attInfo) override;
		void	SetCurrentHP		(size_t hp) override;
		void	RestoreHealth		() override;
		void	SetRegenModule		(HPRegenModule* Module);

		size_t			GetCurrentHP	()	const override { return CurrentHP; }
		size_t			GetMaxHP		()	const override { return BattleStats.GetMaxHP(); }
		HPRegenModule*	GetRegenModule	()	const { return RegenModule; }

		const EntityBattleStats& GetStats() const {
			return BattleStats;
		}

	private:
		EntityBattleStats&	BattleStats;
		HPRegenModule*		RegenModule	= nullptr;
		IndicatorFill&		HPBar;
		size_t				CurrentHP	= 1;

		class StatChangedEvSubs : public IEventSubscriber<int> {
		public:
			StatChangedEvSubs(EntityHPModule& Owner)
				:Owner(Owner){}

			void Execute(int& args) override {

				if ((EntityBattleStatType)args == EntityBattleStatType::MaxHP) {
					size_t hp = Owner.GetCurrentHP();
					float rel = (float)hp/ (float)Owner.GetMaxHP();
					size_t resHP = (size_t)((float)hp * rel);
					Owner.SetCurrentHP(resHP);
				}
			}

		private:
			EntityHPModule& Owner;
		};

		StatChangedEvSubs* Subscriber;
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
		HPRegenModule(EntityHPModule& HPModule)
			:HPModule(HPModule){

		}

		virtual void Regen(CallbackRecArgs_Upd& args) = 0;

		EntityHPModule&			HPModule;
		bool					IsActive		= true;
	};
}