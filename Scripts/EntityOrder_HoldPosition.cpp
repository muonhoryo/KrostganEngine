
#include <EntityOrder_HoldPosition.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_HoldPosition::EntityOrder_HoldPosition(OrdersExecutor& Owner) : IEntityOrder(),
Owner(Owner) {
}

void EntityOrder_HoldPosition::OnStartExecution() {

	auto& modul = Owner.GetAutoAggrModule();
	modul.TurnTargetFollowingOff();
	modul.Restart();
}
void EntityOrder_HoldPosition::OnEndExecution() {

	Owner.GetAutoAggrModule().TurnTargetFollowingOn();
}
EntityOrderType EntityOrder_HoldPosition::GetOrderType() {
	return EntityOrderType::HoldPosition;
}