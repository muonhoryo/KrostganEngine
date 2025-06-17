
#include <EntityOrder_AttackTarget.h>
#include <Extensions.h>
#include <Engine.h>
#include <EntityAction_AutoAttack.h>
#include <EntityAction_FollowObject.h>

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
	list<IEntityAction*>& actions=*new list<IEntityAction*>();
	if (Owner.GetAAModule().CheckTargetReach(Target)) {			//Target is in attack range of executor
		
		actions.push_back((IEntityAction*)new EntityAction_AutoAttack(Owner, Target));
	}
	else {									//Owner needs to follow target first
		
		float alloDist = Owner.GetBattleStats().GetAARadius();
		actions.push_back((IEntityAction*)new EntityAction_FollowObject(Owner,OwnerTransform, Target, alloDist));
		actions.push_back((IEntityAction*)new EntityAction_AutoAttack(Owner, Target));
	}
	return &actions;
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