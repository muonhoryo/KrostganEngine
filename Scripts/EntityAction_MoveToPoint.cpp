
#include <EntityAction_MoveToPoint.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;

EntityAction_MoveToPoint::EntityAction_MoveToPoint(OrdersExecutor& Owner, WorldTransfObj& OwnerTransform,Vector2f TargetGlobalCoord)
	:EntityAction_MoveTo(Owner,OwnerTransform),
	TargetGlobalCoord(TargetGlobalCoord){
}

bool EntityAction_MoveToPoint::CheckExecCondition() {
	return GetCantMoveState() || IsDataInv||DistToTarget <= eps;
}
void EntityAction_MoveToPoint::Execute() {
	MoveTo(TargetGlobalCoord);
}