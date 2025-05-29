#pragma once

#include <EntityOrder_HoldPosition.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_Cancel : public EntityOrder_HoldPosition {
	public:
		EntityOrder_Cancel(OrdersExecutor& Owner);

		virtual void OnStartExecution() override;
		virtual EntityOrderType GetOrderType() override;
		virtual bool CheckExecCondition() override;

	private:
		Clock ComplTimer;
		float CancelTime;
	};
}