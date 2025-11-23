#pragma once

#include <AutoAttackModule.h>
#include <Entity.h>

namespace KrostganEngine::GameObjects {
	class EntityAutoAttackModule final : public AutoAttackModule {
		
	public:
		virtual ~EntityAutoAttackModule() {
			
			Stats.ChangeCurrAAStatsEvent.Remove(OnAAStatsChangedAction);
		}
		EntityAutoAttackModule(AutoAttackAnimation& AAAnimation, Entity& Owner)
			:AutoAttackModule(AAAnimation,*Owner.GetBattleStats().GetCurrAAStats(),Owner),
			Stats(Owner.GetBattleStats()),
			OnAAStatsChangedAction(OnAAStatsChanged(*this))
		{
			Stats.ChangeCurrAAStatsEvent.Add(OnAAStatsChangedAction);
		}

	private:
		class OnAAStatsChanged : public IEventSubscriber<const int> {

		public:
			OnAAStatsChanged(EntityAutoAttackModule& Owner)
				:Owner(Owner){}

			void Execute(const int& args) override {
				Owner.SetAAStats(*Owner.Stats.GetCurrAAStats());
			}

		private:
			EntityAutoAttackModule& Owner;
		};

		EntityBattleStats& Stats;
		OnAAStatsChanged OnAAStatsChangedAction;
	};
}