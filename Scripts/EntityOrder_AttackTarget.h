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
			WorldTransfObj&						OwnerTransform,
			watch_ptr_handler_wr<IAttackableObj>	Target);
		virtual ~EntityOrder_AttackTarget();

		bool CheckExecCondition() override;
		list<IEntityAction*>* GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		const ITransformableObj* GetTarget() const override;

		OrdersExecutor& Owner;
		//Cashed
		AutoAttackModule& AAModule;
		watch_ptr_handler_wr<IAttackableObj> Target;
	};
}