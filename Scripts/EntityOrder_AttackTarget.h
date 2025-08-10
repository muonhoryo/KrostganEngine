#pragma once

#include <OrdersExecutor.h>
#include <EntityOrder_ObjectTarget.h>
#include <EntityOrder_AttackTarget.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_AttackTarget:public IEntityOrder,public EntityOrder_ObjectTarget {
	public:
		EntityOrder_AttackTarget
			(OrdersExecutor&						Owner, 
			TransformableObj&						OwnerTransform,
			watch_ptr_handler_wr<IAttackableObj>	Target);
		~EntityOrder_AttackTarget();

		bool CheckExecCondition() override;
		list<IEntityAction*>* GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		const ITransfObj* GetTarget() const override;

		OrdersExecutor& Owner;
		TransformableObj& OwnerTransform;
		//Cashed
		AutoAttackModule& AAModule;
		watch_ptr_handler_wr<IAttackableObj> Target;
	};
}