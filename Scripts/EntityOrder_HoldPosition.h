#pragma once

#include <OrdersExecutor.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_HoldPosition :public IEntityOrder {
	public:
		EntityOrder_HoldPosition(OrdersExecutor& Owner);

		virtual bool CheckExecCondition() override { return false; }
		virtual list<IEntityAction*>* GetActions() override { return nullptr; }
		virtual void OnStartExecution() override;
		virtual void OnEndExecution() override;
		virtual EntityOrderType GetOrderType() override;

		bool IsCancelNextOrders() override { return true; }

		OrdersExecutor& Owner;
	};
}