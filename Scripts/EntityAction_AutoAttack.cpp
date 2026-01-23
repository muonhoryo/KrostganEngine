
#include <EntityAction_AutoAttack.h>
#include <Engine.h>
#include <Extensions.h>
#include <iostream>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityAction_AutoAttack::EntityAction_AutoAttack(
	OrdersExecutor&							Owner, 
	watch_ptr_handler_wr<IAttackableObj>	Target,
	EntityBattleStats*						Target_BatStats)
		:IEntityAction(),
			Owner(Owner),
			Target(Target),
			AAModule(Owner.GetAAModule()),
			Target_BatStats(Target_BatStats)
{
	WarFogCheckDelayTimer.restart();
}

bool EntityAction_AutoAttack::CheckExecCondition() {

	if (Owner.GetAAModule().GetCurrAAStats() == nullptr)	//Owner cannot auto-attacking now
		return true;

	if (!AAModule.CheckTargetReach())	//Target is untargetable for AA or disappeared
		return true;

	if (WarFogCheckDelayTimer.getElapsedTime().asSeconds() < Engine::GetGlobalConsts().WarFogObserving_CheckTick) {
		return false;
	}

	WarFogCheckDelayTimer.restart();

	float stealth = Target_BatStats == nullptr ? FLT_MAX : Target_BatStats->GetStealth().Stat;
	return !WarFogObserversManager::GetInstance()->Intersect(
		Target.GetPtr_t_c()->GetGlobalPosition(),
		Owner.GetFraction(), 
		stealth);

}
void EntityAction_AutoAttack::Execute() {
	if(Target.GetPtr_t()!=nullptr)
		AAModule.TryDealDamageToTarget();
}
