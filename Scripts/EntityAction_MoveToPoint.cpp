
#include <EntityAction_MoveToPoint.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;

EntityAction_MoveToPoint::EntityAction_MoveToPoint(Entity& Owner,Vector2f TargetGlobalCoord)
	:EntityAction_MoveTo(Owner),
	TargetGlobalCoord(TargetGlobalCoord){
}

bool EntityAction_MoveToPoint::CheckExecCondition() {
	return DistToTarget <= eps;
}
void EntityAction_MoveToPoint::Execute() {
	MoveTo(TargetGlobalCoord);
}