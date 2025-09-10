#pragma once

#include <SFML/System.hpp>
#include <OrdersExecutor.h>
#include <EntityOrder_ObjectTarget.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_FollowTarget :public IEntityOrder, public EntityOrder_ObjectTarget {
	public:
		EntityOrder_FollowTarget
			(OrdersExecutor&							Owner, 
			WorldTransfObj&							OwnerTransform, 
			watch_ptr_handler_wr_c<TransformableObj>	Target);
		~EntityOrder_FollowTarget();

		bool CheckExecCondition() override;
		list<IEntityAction*>* GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		const TransformableObj* GetTarget() const override;

		OrdersExecutor& Owner;
		WorldTransfObj& OwnerTransform;
		watch_ptr_handler_wr_c<TransformableObj> Target;
		Clock FollRepeatTimer;
		bool FirstExec = true;
	};
}