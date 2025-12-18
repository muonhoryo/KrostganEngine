#pragma once

#include <OrdersExecutor.h>
#include <Physics.h>
#include <RelationsSystem.h>
#include <Entity.h>
#include <watch_ptr.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine;

namespace KrostganEngine::GameObjects {
	class BaseAutoAggrModule : public AutoAggressionModule {
	public:
		struct TargetInfo final {

			TargetInfo(watch_ptr_handler_wr<IAttackableObj>& Target)
					:Target(Target)
			{}
			~TargetInfo() {
				delete& Target;
			}

			watch_ptr_handler_wr<IAttackableObj>& Target;
		};

		BaseAutoAggrModule(Entity& Owner, ExecutorActionsMediator& ActionMediator);
		~BaseAutoAggrModule();

		void TurnOnAction() override;
		void TurnOffAction() override;

		void UpdateAction(CallbackRecArgs_Upd& args) override;
		bool GetActivityState() const override;

		IAttackableObj* GetCurrTarget() const;

	private:
		class OnAAStatsChanged final : public IEventSubscriber<const int> {

		public:
			OnAAStatsChanged(BaseAutoAggrModule& Owner)
				:Owner(Owner) {}

			void Execute( const int& args) override {
				if (args == -1)
					Owner.TurnFindTargetState();
			}

		private:
			BaseAutoAggrModule& Owner;
		};
		class OnFractionChanged final : public IEventSubscriber<const IFractionMember::ChangeFractionEvArgs> {

		public:
			OnFractionChanged(BaseAutoAggrModule& Owner)
				:Owner(Owner)
			{}

			void Execute(IFractionMember::ChangeFractionEvArgs const& args) override {
				
				auto tar = dynamic_cast<IAttackableObj*>(&args.Owner);
				if (Owner.GetCurrTarget() == tar) {

					if (FractionsSystem::GetRelation(Owner.Owner.GetFraction(), args.NewFraction) != Relation::Enemy) {
						Owner.Restart();
					}
				}
			}

		private:
			BaseAutoAggrModule& Owner;
		};

		void CheckCurrTarget(CallbackRecArgs_Upd& args);
		void FindTarget(CallbackRecArgs_Upd& args);
		void TurnFindTargetState();

		/// <summary>
		/// Return false if target cannot be reached
		/// </summary>
		/// <returns></returns>
		bool CheckTargetReachability() const;

		TargetInfo* TarInfo;
		OnFractionChanged OnFracChangedSub;
		Entity& Owner;

		bool HasTarget;
		bool IsAttack;

		vector<IPhysicalObject*> TargsBuffer;
		Clock TargetCheckDelay;

		OnAAStatsChanged OnStatsChangedAct;

		static inline const PhysicsLayer TARGETS_MASK = (PhysicsLayer)((int)PhysicsLayer::Buildings | (int)PhysicsLayer::Units);
	};
}