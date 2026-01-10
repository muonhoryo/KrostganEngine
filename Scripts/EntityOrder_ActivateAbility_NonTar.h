#pragma once

#include <OrdersExecutor.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_ActivateAbility_NonTar :public IEntityOrder {
	public:
		EntityOrder_ActivateAbility_NonTar(OrdersExecutor& Owner, size_t AbilityIndex);

		virtual bool CheckExecCondition() override { return false; }
		virtual list<IEntityAction*>* GetActions() override { return nullptr; }
		virtual void OnStartExecution() override;
		virtual void OnEndExecution() override{}
		virtual EntityOrderType GetOrderType() override;

		OrdersExecutor& Owner;
		size_t AbilityIndex;
	};
}