
#include <EntityAction_AutoAttack.h>
#include <Engine.h>
#include <Extensions.h>
#include <iostream>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityAction_AutoAttack::EntityAction_AutoAttack(OrdersExecutor& Owner, watch_ptr_handler_wr<IAttackableObj> Target)
	:IEntityAction(),
	Owner(Owner),
	Target(Target),
	AAModule(Owner.GetAAModule())
{}

bool EntityAction_AutoAttack::CheckExecCondition() {

	if (Owner.GetAAModule().GetCurrAAStats() == nullptr)	//Owner cannot auto-attacking now
		return true;

	return !AAModule.CheckTargetReach();	//Target is untargetable for AA or disappeared
}
void EntityAction_AutoAttack::Execute() {
	if(Target.GetPtr_t()!=nullptr)
		AAModule.TryDealDamageToTarget();
}
