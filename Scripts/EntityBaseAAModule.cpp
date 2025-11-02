
#include <EntityBaseAAModule.h>
#include <Extensions.h>
#include <Engine.h>
#include <LineAAAnimation.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Visual;

EntityBaseAAModule::EntityBaseAAModule(EntityBattleStats& BattleStats,WorldTransfObj& Owner)
	:AutoAttackModule(*new LineAAAnimation(Owner)),
	BattleStats(BattleStats),
	Owner(Owner){

	auto stats = BattleStats.GetAAStats();
	if (stats == nullptr || stats->GetAASpeed() <= eps)
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
	
	auto stats = BattleStats.GetAAStats();
	if (stats == nullptr)
		return false;

	Vector2f pos = Owner.GetGlobalPosition();
	Vector2f closPoint = potentTarget.GetClosestPoint(pos);
	float dist = Length(closPoint - pos);
	return dist - stats->GetAARange() <= eps;
}
bool EntityBaseAAModule::TryDealDamageToTarget() {
	if (CheckTargetReach())
	{
		if (RemReloadTime <= 0) {

			auto stats = BattleStats.GetAAStats();
			if (stats == nullptr)
			{
				RemReloadTime = FLT_MAX;
				return true;
			}

			size_t dealedDmg = stats->GetAADamage();
			AutoAttackHitInfo attInfo = AutoAttackHitInfo(dealedDmg,watch_ptr_handler_wr<IAttackableObj>(*Target), *stats);
			Target->GetPtr_t()->GetHPModule().TakeDamage(attInfo);
			if (stats->GetAASpeed() <= eps) {

				RemReloadTime = FLT_MAX;
			}
			else {

				RemReloadTime = stats->GetAACooldown();
				AAAnimation.OnDealDmg(attInfo);
			}
			return true;
		}
	}
	return false;
}