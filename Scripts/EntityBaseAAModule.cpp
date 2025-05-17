
#include <EntityBaseAAModule.h>
#include <Extensions.h>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

EntityBaseAAModule::EntityBaseAAModule(EntityBattleStats& BattleStats,TransformableObj& Owner)
	:AutoAttackModule(),
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
	Target = target;
}
bool EntityBaseAAModule::CheckTargetReach() {
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
			Target->GetHPModule().TakeDamage(dealedDmg);
			float aaSpeed = BattleStats.GetAASpeed();
			if (aaSpeed == 0)
				RemReloadTime = FLT_MAX;
			else
				RemReloadTime = (float)1 / aaSpeed;
			return true;
		}
	}
	return false;
}