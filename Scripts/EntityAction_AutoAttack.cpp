
#include <EntityAction_AutoAttack.h>
#include <Engine.h>
#include <Extensions.h>
#include <iostream>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityAction_AutoAttack::EntityAction_AutoAttack(OrdersExecutor& Owner, IAttackableObj& Target)
	:IEntityAction(),
	Owner(Owner),
	Target(Target),
	TargetHPModule(Target.GetHPModule()),
	AAModule(Owner.GetAAModule())
{}

bool EntityAction_AutoAttack::CheckExecCondition() {
	if (TargetHPModule.GetIsDeadState())
		return true;
	return !AAModule.CheckTargetReach();
}
void EntityAction_AutoAttack::Execute() {
	AAModule.TryDealDamageToTarget();
}
