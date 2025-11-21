
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
	//TargetHPModule(Target.GetPtr_t()->GetHPModule()),
	AAModule(Owner.GetAAModule())
{}

bool EntityAction_AutoAttack::CheckExecCondition() {

	IAttackableObj* ptr = Target.GetPtr_t();
	if (ptr == nullptr || !ptr->CheckAttackReachability(IAttackableObj::AtkParam::IsAA))
		return true;
	return !AAModule.CheckTargetReach();
}
void EntityAction_AutoAttack::Execute() {
	if(Target.GetPtr_t()!=nullptr)
		AAModule.TryDealDamageToTarget();
}
