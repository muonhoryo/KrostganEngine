
#include <EntityOrder_MoveToPoint.h>
#include <EntityAction_MoveToPoint.h>
#include <Extensions.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_MoveToPoint::EntityOrder_MoveToPoint(OrdersExecutor& Owner, TransformableObj& OwnerTransform,Vector2f TargetGlobalCoord) : EntityOrder_GlobalPosTarget(TargetGlobalCoord),
	Owner(Owner),
	OwnerTransform(OwnerTransform){
}

bool EntityOrder_MoveToPoint::CheckExecCondition() {
	if (IsDataInv)
		return true;
	float dist = Length(TargetGlobalPos - OwnerTransform.GetPosition());
	return dist <= eps;
}
list <IEntityAction*>& EntityOrder_MoveToPoint::GetActions() {
	list<IEntityAction*>* lst = new list<IEntityAction*>();
	IEntityAction* act = new EntityAction_MoveToPoint(Owner,OwnerTransform, TargetGlobalPos);
	lst->push_back(act);
	return *lst;
}
void EntityOrder_MoveToPoint::OnStartExecution()
{
	Owner.GetAutoAggrModule().TurnOff();
}
void EntityOrder_MoveToPoint::OnEndExecution() 
{
	Owner.GetAutoAggrModule().TurnOn();
}
EntityOrderType EntityOrder_MoveToPoint::GetOrderType() {
	return EntityOrderType::MovingToPoint;
}