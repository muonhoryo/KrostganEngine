#pragma once

#include <OrdersExecutor.h>
#include <EntityOrder_ObjectTarget.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_AttackTarget:public IEntityOrder,public EntityOrder_ObjectTarget {
	public:
		EntityOrder_AttackTarget(OrdersExecutor& Owner, TransformableObj& OwnerTransform, IAttackableObj& Target);

		bool CheckExecCondition() override;
		list<IEntityAction*>& GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		const TransformableObj& GetTarget() const override;

		OrdersExecutor& Owner;
		TransformableObj& OwnerTransform;
		//Cashed
		AutoAttackModule& AAModule;
		IAttackableObj& Target;
	};
}