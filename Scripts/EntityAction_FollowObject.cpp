
#include <EntityAction_FollowObject.h>
#include <Engine.h>
#include <Extensions.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;


EntityAction_FollowObject::EntityAction_FollowObject(Entity& Owner, const TransformableObj& Target, const float DistToFoll)
	:EntityAction_MoveTo(Owner),
	Target(Target),
	DistToFoll(DistToFoll){
}

bool EntityAction_FollowObject::CheckExecCondition() {
	return DistToTarget-DistToFoll <= eps;
}
void EntityAction_FollowObject::Execute() {
	MoveTo(Target.GetPosition());
}