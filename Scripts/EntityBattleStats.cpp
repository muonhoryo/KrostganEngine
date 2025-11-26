
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityBattleStats::EntityBattleStats(AutoAttackStats* AAStats) {

	if (AAStats != nullptr) {
		CurrAAStats = 0;
		SavedAAStats.push_back(AAStats);
	}

	InitializeDefaultStats();
}
EntityBattleStats::EntityBattleStats(const vector<AutoAttackStats*>& AAStats) {

	SavedAAStats = AAStats;
	if (AAStats.size() != 0)
		CurrAAStats = 0;

	InitializeDefaultStats();
}
EntityBattleStats::EntityBattleStats(const EntityBattleStats& copy)
	:ModifiableStatsWrapper(copy) {

	copy.CopyTo_Internal(*this);
}
EntityBattleStats::~EntityBattleStats() {

	for (auto stats : SavedAAStats)
		delete stats;
}
void EntityBattleStats::InitializeDefaultStats() {
	
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

	toCopy.CurrAAStats = CurrAAStats;
	size_t size = SavedAAStats.size();
	if (size != 0) {
		
		for (auto stats : toCopy.SavedAAStats) {
			delete stats;
		}
		toCopy.SavedAAStats.clear();

		toCopy.SavedAAStats = vector<AutoAttackStats*>(size);
		for (size_t i = 0;i < size;++i) {
			toCopy.SavedAAStats[i] = new AutoAttackStats(*SavedAAStats[i]);
		}
 	}
}

//
//
// AutoAttackStats
//
//

AutoAttackStats* EntityBattleStats::GetCurrAAStats() const { return CurrAAStats >= 0 ? SavedAAStats[CurrAAStats] : nullptr; }
void EntityBattleStats::SetAAStats(int index) {

	if (index<-1 || index>((int)SavedAAStats.size()-1))
		throw exception("Invalid index of SavedAAStats");

	CurrAAStats = index;
	ChangeCurrAAStatsEventHan.Execute(CurrAAStats);
}
size_t EntityBattleStats::GetSavedAAStatsCount() const {
	return SavedAAStats.size();
}
int EntityBattleStats::GetCurrAAStatsIndex() const {
	return CurrAAStats;
}

void EntityBattleStats::SetAAStats(const AutoAttackStats* stats) {

	if (stats == nullptr) {
		CurrAAStats = -1;
		ChangeCurrAAStatsEventHan.Execute(-1);
	}
	else {

		auto index = CollectionsExts::IndexOf(SavedAAStats, stats);
		if (index == string::npos)
			throw exception("Input AAStats didn't push in saved AutoAttackStats's");

		CurrAAStats = index;
		ChangeCurrAAStatsEventHan.Execute(CurrAAStats);
	}

}
int EntityBattleStats::AddAAStats(AutoAttackStats& stats) {

	if (CollectionsExts::Contains(SavedAAStats, &stats))
		throw exception("AAStats already contain input stats");

	SavedAAStats.push_back(&stats);
	return SavedAAStats.size() - 1;
}
void EntityBattleStats::RemoveAAStats(const AutoAttackStats& stats) {

	if (!CollectionsExts::Remove(SavedAAStats,&stats))
		throw exception("Input stats is not in SavedAAStats");
}
void EntityBattleStats::RemoveAAStats(size_t index) {

	if (index <= SavedAAStats.size())
		throw exception("Index out of range");

	auto it = SavedAAStats.begin();
	it += index;
	SavedAAStats.erase(it);
}

//
//
// Parameters
//
//

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