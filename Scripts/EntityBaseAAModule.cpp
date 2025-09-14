
#include <EntityBaseAAModule.h>
#include <Extensions.h>
#include <Engine.h>
#include <LineAAAnimation.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

EntityBaseAAModule::EntityBaseAAModule(EntityBattleStats& BattleStats,WorldTransfObj& Owner)
	:AutoAttackModule(*new LineAAAnimation(Owner)),
	BattleStats(BattleStats),
	Owner(Owner){
	if (BattleStats.GetAASpeed() <= eps)
		RemReloadTime = FLT_MAX;
}

/// <summary>
/// If target is nullptr, stops AAModule
/// </summary>
/// <param name="target"></param>
void EntityBaseAAModule::SetAsTarget(watch_ptr_handler_wr<IAttackableObj>* target) {

	if (Target != nullptr)
		delete Target;

	if (target != nullptr &&
		target->GetPtr_t()!=nullptr) {

		Target = target;
	}
	else
	{
		Target = nullptr;
	}
}
bool EntityBaseAAModule::CheckTargetReach() {

	if (Target == nullptr)
		return false;
	auto ptr = Target->GetPtr_t();
	if(ptr==nullptr || ptr->GetHPModule().DeathModule.GetIsDeadState())
		return false;
	return CheckTargetReach(*ptr);
}
bool EntityBaseAAModule::CheckTargetReach(const IAttackableObj& potentTarget) {
	Vector2f pos = Owner.GetGlobalPosition();
	Vector2f closPoint = potentTarget.GetClosestPoint(pos);
	float dist = Length(closPoint - pos);
	return dist - BattleStats.GetAARange() <= eps;
}
bool EntityBaseAAModule::TryDealDamageToTarget() {
	if (CheckTargetReach())
	{
		if (RemReloadTime <= 0) {
			size_t dealedDmg = BattleStats.GetAADamage();
			float aaSpeed = BattleStats.GetAASpeed();
			AutoAttackInfo attInfo = AutoAttackInfo(dealedDmg,watch_ptr_handler_wr<IAttackableObj>(*Target), aaSpeed);
			Target->GetPtr_t()->GetHPModule().TakeDamage(attInfo);
			if (BattleStats.GetAASpeed() == 0) {

				RemReloadTime = FLT_MAX;
			}
			else {

				RemReloadTime = BattleStats.GetAACooldown();
				AAAnimation.OnDealDmg(attInfo);
			}
			return true;
		}
	}
	return false;
}