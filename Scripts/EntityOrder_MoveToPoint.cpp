
#include <EntityOrder_MoveToPoint.h>
#include <EntityAction_MoveToPoint.h>
#include <Extensions.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_MoveToPoint::EntityOrder_MoveToPoint(Entity& Owner,Vector2f TargetGlobalCoord)
	:EntityOrder_GlobalPosTarget(TargetGlobalCoord),
	Owner(Owner){
}

bool EntityOrder_MoveToPoint::CheckExecCondition() {
	float dist = Length(TargetGlobalPos - Owner.GetPosition());
	return dist <= eps;
}
list <IEntityAction*>& EntityOrder_MoveToPoint::GetActions() {
	list<IEntityAction*>* lst = new list<IEntityAction*>();
	IEntityAction* act = new EntityAction_MoveToPoint(Owner, TargetGlobalPos);
	lst->push_back(act);
	return *lst;
}
void EntityOrder_MoveToPoint::OnStartExecution() {}
void EntityOrder_MoveToPoint::OnEndExecution() {}
EntityOrderType EntityOrder_MoveToPoint::GetOrderType() {
	return EntityOrderType::MovingToPoint;
}