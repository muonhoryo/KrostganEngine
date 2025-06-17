
#include <EntityBaseAAModule.h>
#include <Extensions.h>
#include <Engine.h>
#include <LineAAAnimation.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

EntityBaseAAModule::EntityBaseAAModule(EntityBattleStats& BattleStats,TransformableObj& Owner)
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
void EntityBaseAAModule::SetAsTarget(IAttackableObj* target) {
	if (target != nullptr) {

		Target = target;
	}
	else
	{
		Target = nullptr;
	}
}
bool EntityBaseAAModule::CheckTargetReach() {
	if (Target->GetHPModule().DeathModule.GetIsDeadState())
		return false;
	return CheckTargetReach(*Target);
}
bool EntityBaseAAModule::CheckTargetReach(const IAttackableObj& potentTarget) {
	Vector2f pos = Owner.GetPosition();
	Vector2f closPoint = potentTarget.GetClosestPoint(pos);
	float dist = Length(closPoint - pos);
	return dist - BattleStats.GetAARadius() <= eps;
}
bool EntityBaseAAModule::TryDealDamageToTarget() {
	if (CheckTargetReach())
	{
		if (RemReloadTime <= 0) {
			size_t dealedDmg = BattleStats.GetAADamage();
			float aaSpeed = BattleStats.GetAASpeed();
			AutoAttackInfo attInfo = AutoAttackInfo(dealedDmg,*Target, aaSpeed);
			Target->GetHPModule().TakeDamage(attInfo);
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