
#include <EntityOrder_AttackTarget.h>
#include <Extensions.h>
#include <Engine.h>
#include <EntityAction_AutoAttack.h>
#include <EntityAction_FollowObject.h>
#include <PathFinding_Diijkstra.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Core;

EntityOrder_AttackTarget::EntityOrder_AttackTarget(OrdersExecutor& Owner,TransformableObj& OwnerTransform, 
	watch_ptr_handler_wr<IAttackableObj> Target)
	:IEntityOrder(),
	Owner(Owner),
	OwnerTransform(OwnerTransform),
	Target(Target),
	AAModule(Owner.GetAAModule())
{}
EntityOrder_AttackTarget::~EntityOrder_AttackTarget() {

}

bool EntityOrder_AttackTarget::CheckExecCondition() {
	
	IAttackableObj* ptr = Target.GetPtr_t();
	return ptr==nullptr || ptr->GetHPModule().DeathModule.GetIsDeadState();
}
list<IEntityAction*>* EntityOrder_AttackTarget::GetActions() {

	IAttackableObj* ptr = Target.GetPtr_t();
	if (ptr == nullptr)
		return nullptr;

	list<IEntityAction*>* lst = new list<IEntityAction*>();

	if (Owner.GetAAModule().CheckTargetReach(*ptr)) {			//Target is in attack range of executor

		EntityAction_AutoAttack* act = new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(Target));
		lst->push_back((IEntityAction*)act);
	}
	else {									//Owner needs to follow target first

		Segment ray(OwnerTransform.GetPosition(), ptr->GetPosition());
		if (Engine::GetPhysicsEngine().RayHit(ray,
			(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings)))
		{
			list<Vector2f>* pnts = PathFinding_Diijkstra::GetPath(ray.First, ray.Second);
			if (pnts != nullptr && pnts->size() >1) {

				typename list<Vector2f>::iterator end = pnts->end();
				--end;
				for (auto it = pnts->begin(); it != end;++it) {

					IEntityAction* act = new EntityAction_MoveToPoint(Owner, OwnerTransform, *it);
					lst->push_back(act);
				}
			}
		}
		float alloDist = Owner.GetBattleStats().GetAARadius();
		EntityAction_FollowObject* folAct = new EntityAction_FollowObject(Owner, OwnerTransform, 
			*new watch_ptr_handler_wr_c<TransformableObj>(Target),
			alloDist);
		EntityAction_AutoAttack* aaAct = new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(Target));
		lst->push_back((IEntityAction*)folAct);
		lst->push_back((IEntityAction*)aaAct);
	}

	return lst;
}
void EntityOrder_AttackTarget::OnStartExecution() 
{
	Owner.GetAutoAggrModule().TurnOff();
	AAModule.SetAsTarget(new watch_ptr_handler_wr<IAttackableObj>(Target));
}
void EntityOrder_AttackTarget::OnEndExecution() 
{
	Owner.GetAutoAggrModule().TurnOn();
	AAModule.SetAsTarget(nullptr);
}
EntityOrderType EntityOrder_AttackTarget::GetOrderType() {
	return EntityOrderType::AttackTarget;
}

const TransformableObj* EntityOrder_AttackTarget::GetTarget() const {
	return Target.GetPtr_t_c();
}