

#include <EntityOrder_FollowTarget.h>
#include <Extensions.h>
#include <Engine.h>
#include <EntityAction_AutoAttack.h>
#include <EntityAction_FollowObject.h>
#include <PathFinding_Diijkstra.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_FollowTarget::EntityOrder_FollowTarget
	(OrdersExecutor&							Owner, 
	WorldTransfObj&							OwnerTransform, 
	watch_ptr_handler_wr_c<TransformableObj>		Target)
	:IEntityOrder(),
	EntityOrder_ImmobilityChecking(OwnerTransform),
		Owner			(Owner),
		Target			(Target)
{}
EntityOrder_FollowTarget::~EntityOrder_FollowTarget() {
}

bool EntityOrder_FollowTarget::CheckExecCondition() {
	auto ptr = Target.GetPtr_t();
	return ptr == nullptr || CheckImmobility(ptr->GetGlobalPosition());
}
list<IEntityAction*>* EntityOrder_FollowTarget::GetActions() {

	auto ptr = Target.GetPtr_t();
	if (ptr == nullptr)
		return nullptr;

	list<IEntityAction*>* lst = new list<IEntityAction*>();

	Segment ray(OwnerTransform.GetGlobalPosition(), ptr->GetGlobalPosition());
	if (Engine::GetPhysicsEngine().RayHit(ray,
		(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings)))
	{
		IEntityAction* act = nullptr;
		list<Vector2f>* pnts = PathFinding_Diijkstra::GetPath(ray.First, ray.Second);
		if (pnts != nullptr && pnts->size() > 1) {
			typename list<Vector2f>::iterator end = pnts->end();
			--end;
			for (auto it = pnts->begin(); it != end;++it) {

				act= new EntityAction_MoveToPoint(Owner, OwnerTransform, *it);
				lst->push_back(act);
			}
		}
		act = new EntityAction_FollowObject(Owner, OwnerTransform, Target, eps);
		lst->push_back(act);
		return lst;
	}
	else {

		float dist = Length(OwnerTransform.GetGlobalPosition() - ptr->GetGlobalPosition());
		if (dist > eps) {	//Owner is too far from target

			if (FirstExec) {		//Immidiet first execution

				FirstExec = false;
				lst->push_back(new EntityAction_FollowObject(Owner,OwnerTransform,Target,eps));
			}
			else if (FollRepeatTimer.getElapsedTime().asSeconds() > Engine::GetGlobalConsts().EntityAct_RepCoolDown) {		//Limit requests to follow

				FollRepeatTimer.restart();
				lst->push_back(new EntityAction_FollowObject(Owner, OwnerTransform, Target, eps));
			}
			return lst;
		}
	}
	return nullptr;
}
void EntityOrder_FollowTarget::OnStartExecution()
{
	Owner.GetAutoAggrModule().TurnOff();
}
void EntityOrder_FollowTarget::OnEndExecution()
{
	Owner.GetAutoAggrModule().TurnOn();
}
EntityOrderType EntityOrder_FollowTarget::GetOrderType() {
	return EntityOrderType::FollowTarget;
}

const TransformableObj* EntityOrder_FollowTarget::GetTarget() const {
	return Target.GetPtr_t();
}