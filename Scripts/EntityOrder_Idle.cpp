
#include <EntityOrder_Idle.h>
#include <iostream>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_Idle::EntityOrder_Idle(OrdersExecutor& Owner) : IEntityOrder(),
	Owner(Owner){
}

void EntityOrder_Idle::OnStartExecution() {
	Owner.GetAutoAggrModule().TurnOff();
}
void EntityOrder_Idle::OnEndExecution() {
	Owner.GetAutoAggrModule().TurnOn();
}
EntityOrderType EntityOrder_Idle::GetOrderType() {
	return EntityOrderType::Idle;
}