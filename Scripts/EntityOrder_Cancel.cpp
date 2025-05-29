
#include <EntityOrder_Cancel.h>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

EntityOrder_Cancel::EntityOrder_Cancel(OrdersExecutor& Owner) : EntityOrder_HoldPosition(Owner),
	CancelTime(Engine::GetGlobalConsts().Orders_CancelTime){
}
void EntityOrder_Cancel::OnStartExecution() {
	EntityOrder_HoldPosition::OnStartExecution();
	ComplTimer.restart();
;}
EntityOrderType EntityOrder_Cancel::GetOrderType() {
	return EntityOrderType::Cancel;
}
bool EntityOrder_Cancel::CheckExecCondition() {
	return ComplTimer.getElapsedTime().asSeconds() >= CancelTime;
}