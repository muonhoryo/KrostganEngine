
#include <EntityOrder_AttackArea.h>
#include <EntityAction_MoveToPoint.h>
#include <Extensions.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_AttackArea::EntityOrder_AttackArea(OrdersExecutor& Owner, TransformableObj& OwnerTransform, Vector2f TargetGlobalCoord) : EntityOrder_GlobalPosTarget(TargetGlobalCoord),
Owner(Owner),
OwnerTransform(OwnerTransform) {
}

bool EntityOrder_AttackArea::CheckExecCondition() {
	float dist = Length(TargetGlobalPos - OwnerTransform.GetPosition());
	return dist <= eps;
}
list <IEntityAction*>* EntityOrder_AttackArea::GetActions() {
	list<IEntityAction*>* lst = new list<IEntityAction*>();
	IEntityAction* act = new EntityAction_MoveToPoint(Owner, OwnerTransform, TargetGlobalPos);
	lst->push_back(act);
	return lst;
}
EntityOrderType EntityOrder_AttackArea::GetOrderType() {
	return EntityOrderType::AttackArea;
}

void EntityOrder_AttackArea::OnStartExecution() {
}
void EntityOrder_AttackArea::OnEndExecution() {

}