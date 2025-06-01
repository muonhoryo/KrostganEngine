

#include <EntityOrder_FollowTarget.h>
#include <Extensions.h>
#include <Engine.h>
#include <EntityAction_AutoAttack.h>
#include <EntityAction_FollowObject.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_FollowTarget::EntityOrder_FollowTarget(OrdersExecutor& Owner, TransformableObj& OwnerTransform, TransformableObj& Target)
	:IEntityOrder(),
	Owner(Owner),
	OwnerTransform(OwnerTransform),
	Target(Target)
{}

bool EntityOrder_FollowTarget::CheckExecCondition() {
	return false;
}
list<IEntityAction*>* EntityOrder_FollowTarget::GetActions() {
	
	float dist = Length(OwnerTransform.GetPosition() - Target.GetPosition());

	if (dist > eps)	{	//Owner is too far from target

		if (FirstExec) {		//Immidiet first execution

			FirstExec = false;
			return new list<IEntityAction*>{ new EntityAction_FollowObject(Owner,OwnerTransform,Target,eps) };
		}
		else if (FollRepeatTimer.getElapsedTime().asSeconds() > Engine::GetGlobalConsts().EntityAct_RepCoolDown) {		//Limit requests to follow

			FollRepeatTimer.restart();
			return new list<IEntityAction*>{ new EntityAction_FollowObject(Owner,OwnerTransform,Target,eps) };
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

const TransformableObj& EntityOrder_FollowTarget::GetTarget() const {
	return Target;
}