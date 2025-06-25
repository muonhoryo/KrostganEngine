
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

EntityOrder_AttackTarget::EntityOrder_AttackTarget(OrdersExecutor& Owner,TransformableObj& OwnerTransform, IAttackableObj& Target)
	:IEntityOrder(),
	Owner(Owner),
	OwnerTransform(OwnerTransform),
	Target(Target),
	AAModule(Owner.GetAAModule())
{}

bool EntityOrder_AttackTarget::CheckExecCondition() {
	return Target.GetHPModule().DeathModule.GetIsDeadState();
}
list<IEntityAction*>* EntityOrder_AttackTarget::GetActions() {
	list<IEntityAction*>* lst = new list<IEntityAction*>();

	if (Owner.GetAAModule().CheckTargetReach(Target)) {			//Target is in attack range of executor

		lst->push_back((IEntityAction*)new EntityAction_AutoAttack(Owner, Target));
	}
	else {									//Owner needs to follow target first

		Segment ray(OwnerTransform.GetPosition(), Target.GetPosition());
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
		lst->push_back((IEntityAction*)new EntityAction_FollowObject(Owner, OwnerTransform, Target, alloDist));
		lst->push_back((IEntityAction*)new EntityAction_AutoAttack(Owner, Target));
	}

	return lst;
}
void EntityOrder_AttackTarget::OnStartExecution() 
{
	Owner.GetAutoAggrModule().TurnOff();
	AAModule.SetAsTarget(&Target);
}
void EntityOrder_AttackTarget::OnEndExecution() 
{
	Owner.GetAutoAggrModule().TurnOn();
	AAModule.SetAsTarget(nullptr);
}
EntityOrderType EntityOrder_AttackTarget::GetOrderType() {
	return EntityOrderType::AttackTarget;
}

const TransformableObj& EntityOrder_AttackTarget::GetTarget() const {
	return Target;
}