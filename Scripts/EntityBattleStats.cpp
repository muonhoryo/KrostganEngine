
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityBattleStats::EntityBattleStats(AutoAttackStats* AAStats) 
	:AAStats(AAStats){

	this->AAStats = AAStats;

	//size_t
	InitializeField_s_t(EntityBattleStatType::MaxHP, 1);
	InitializeField_s_t(EntityBattleStatType::RegenHP_Amount, 0);

	//float
	InitializeField_f(EntityBattleStatType::RegenHP_Tick, 1);
	InitializeField_f(EntityBattleStatType::MovingSpeed, 1);
	InitializeField_f(EntityBattleStatType::AutoAggrRadius, 0);

	//bool
	InitializeField_bool(EntityBattleStatType::IsTargetableForAA, true);
}
EntityBattleStats::EntityBattleStats(const EntityBattleStats& copy)
	:AAStats(nullptr),
	ModifiableStatsWrapper(copy) {

	copy.CopyTo_Internal(*this);
}
EntityBattleStats::~EntityBattleStats() {

	if (AAStats != nullptr)
		delete AAStats;
}
void EntityBattleStats::CopyTo(ModifiableStatsWrapper
	<EntBatStats_Consts::StatType,
	EntBatStats_Consts::FIELDS_COUNT,
	EntBatStats_Consts::StatTypeNames,
	EntBatStats_Consts::FIELDS_COUNT_F,
	EntBatStats_Consts::FIELDS_COUNT_S_T,
	EntBatStats_Consts::FIELDS_COUNT_BOOL>& toCopy) const{

	ModifiableStatsWrapper::CopyTo(toCopy);
	EntityBattleStats* parCopy = dynamic_cast<EntityBattleStats*>(&toCopy);
	CopyTo_Internal(*parCopy);
}
void EntityBattleStats::CopyTo_Internal(EntityBattleStats& toCopy) const {

	if (AAStats != nullptr) {

		if (toCopy.AAStats == nullptr) {
			toCopy.AAStats = new AutoAttackStats(*AAStats);
		}
		else {
			AAStats->CopyTo(*toCopy.AAStats);
		}
	}
}

//size_t
void EntityBattleStats::SetMaxHP(size_t hp) {
	if (hp == 0)
		throw exception("Hit points count must be more than zero");

	SetDefaultStat(EntityBattleStatType::MaxHP, hp);
}
void EntityBattleStats::SetHPRegenAmount(size_t amount) {

	SetDefaultStat(EntityBattleStatType::RegenHP_Amount, amount);
}

//float
void EntityBattleStats::SetHPRegenTick(float tick) {
	if (tick <= 0) {
		return;
	}

	SetDefaultStat(EntityBattleStatType::RegenHP_Tick, tick);
}
void EntityBattleStats::SetMovingSpeed(float speed) {
	if (speed < 0)
		throw exception("Moving spedd cannot be less than zero.");

	SetDefaultStat(EntityBattleStatType::MovingSpeed, speed);
}
void EntityBattleStats::SetAutoAggrRadius(float radius) {
	if (radius < 0)
		throw exception("AutoAggression radius cannot be less than zero");

	SetDefaultStat(EntityBattleStatType::AutoAggrRadius, radius);
}

//bool
void EntityBattleStats::SetTargetableForAA(bool isTargetable) {

	SetDefaultStat(EntityBattleStatType::IsTargetableForAA, isTargetable);
}