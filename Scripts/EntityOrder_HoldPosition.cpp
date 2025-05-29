
#include <EntityOrder_HoldPosition.h>
#include <iostream>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_HoldPosition::EntityOrder_HoldPosition(OrdersExecutor& Owner) : IEntityOrder(),
	Owner(Owner){
}

void EntityOrder_HoldPosition::OnStartExecution() {
	Owner.GetAutoAggrModule().TurnOff();
}
void EntityOrder_HoldPosition::OnEndExecution() {
	Owner.GetAutoAggrModule().TurnOn();
}
EntityOrderType EntityOrder_HoldPosition::GetOrderType() {
	return EntityOrderType::HoldPosition;
}