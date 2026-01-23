#pragma once

#include <OrdersExecutor.h>
#include <EntityOrder_ObjectTarget.h>
#include <EntityOrder_AttackTarget.h>
#include <EntityOrder_ImmobilityChecking.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_AttackTarget:public IEntityOrder,public EntityOrder_ObjectTarget, public virtual EntityOrder_ImmobilityChecking {
	public:
		EntityOrder_AttackTarget
			(OrdersExecutor&						Owner, 
			watch_ptr_handler_wr<IAttackableObj>	Target,
			IFractionMember*						Target_FracMem = nullptr,
			EntityBattleStats*						Target_BatStats = nullptr);
		virtual ~EntityOrder_AttackTarget();

		bool CheckExecCondition() override;
		list<IEntityAction*>* GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		const ITransformableObj* GetTarget() const override;

		watch_ptr_handler_wr<IAttackableObj> Target;
		EntityBattleStats* Target_BatStats;
		//Cashed
		AutoAttackModule& AAModule;

	protected:
		bool IsTargetObserving() const;

	private:
		class OnFractionChanged final : public IEventSubscriber<const IFractionMember::ChangeFractionEvArgs> {

		public:
			OnFractionChanged(EntityOrder_AttackTarget& Owner, IFractionMember& Target)
				:Owner(Owner),
				Target(Target),
				Target_OldFraction(Target.GetFraction())
			{}

			void Execute(IFractionMember::ChangeFractionEvArgs const& args) override {

				if (&Target == &args.Owner) {

					if (args.OldFraction!=args.NewFraction ||
						FractionsSystem::GetRelation(Target_OldFraction, args.NewFraction) != Relation::Enemy) {

						Owner.Owner.CancelOrder(0);
					}
				}
			}

		private:
			EntityOrder_AttackTarget& Owner;
			IFractionMember& Target;
			Fraction Target_OldFraction;
		};

		OnFractionChanged* OnFractionChangedSubs = nullptr;
		mutable Clock TargetCheckDelayTimer = Clock();
	};
}