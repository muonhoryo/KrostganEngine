
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityBattleStats::EntityBattleStats(AutoAttackStats* AAStats) 
	:AAStats(AAStats){

	//size_t
	InitializeField_s_t(EntityBattleStatType::MaxHP, 1);
	InitializeField_s_t(EntityBattleStatType::RegenHP_Amount, 0);

	//float
	InitializeField_f(EntityBattleStatType::RegenHP_Tick, 1);
	InitializeField_f(EntityBattleStatType::MovingSpeed, 1);
	InitializeField_f(EntityBattleStatType::AutoAggrRadius, 0);
}
EntityBattleStats::EntityBattleStats(const EntityBattleStats& copy)
	:ModifiableStatsWrapper(copy) {

	if (copy.AAStats == nullptr)
		AAStats = nullptr;
	else
		AAStats = new AutoAttackStats(*copy.AAStats);
}
EntityBattleStats::~EntityBattleStats() {

	if (AAStats != nullptr)
		delete AAStats;
}

//
// 
//HitPoint
//
//
void EntityBattleStats::SetMaxHP(size_t hp) {
	if (hp == 0)
		throw exception("Hit points count must be more than zero");

	SetDefaultStat(EntityBattleStatType::MaxHP, hp);
}
void EntityBattleStats::SetHPRegenAmount(size_t amount) {

	SetDefaultStat(EntityBattleStatType::RegenHP_Amount, amount);
}
void EntityBattleStats::SetHPRegenTick(float tick) {
	if (tick <= 0) {
		return;
	}

	SetDefaultStat(EntityBattleStatType::RegenHP_Tick, tick);
}
//
//
//Moving
//
//
void EntityBattleStats::SetMovingSpeed(float speed) {
	if (speed < 0)
		throw exception("Moving spedd cannot be less than zero.");

	SetDefaultStat(EntityBattleStatType::MovingSpeed, speed);
}
//
// 
// View
// 
//
void EntityBattleStats::SetAutoAggrRadius(float radius) {
	if (radius < 0)
		throw exception("AutoAggression radius cannot be less than zero");

	SetDefaultStat(EntityBattleStatType::AutoAggrRadius, radius);
}