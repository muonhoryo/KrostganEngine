
#include <EntityAction_FollowObject.h>
#include <Engine.h>
#include <Extensions.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;


EntityAction_FollowObject::EntityAction_FollowObject
	(OrdersExecutor&								Owner, 
	TransformableObj&								OwnerTransform, 
	watch_ptr_handler_wr_c<TransformableObj>	Target,
	const float									DistToFoll)
	:EntityAction_MoveTo	(Owner,OwnerTransform),
	Target		(Target),
	DistToFoll	(DistToFoll){
}
EntityAction_FollowObject::~EntityAction_FollowObject() {
}

bool EntityAction_FollowObject::CheckExecCondition() {
	auto ptr = Target.GetPtr_t();
	return GetCantMoveState() || ptr==nullptr || IsDataInv||DistToTarget-DistToFoll <= eps;
}
void EntityAction_FollowObject::Execute() {
	auto ptr = Target.GetPtr_t();
	if(ptr!=nullptr)
		MoveTo(ptr->GetPosition());
}