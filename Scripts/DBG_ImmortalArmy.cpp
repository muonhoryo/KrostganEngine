
#include <DBG_ImmortalArmy.h>
#include <EntitiesObserver.h>

using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;

DBG_ImmortalArmy::Immortality::Immortality(Entity& BuffsOwner)
	:BuffsOwner(BuffsOwner) {

	auto stats = &BuffsOwner.GetBattleStats();
	auto aaStats = stats->GetCurrAAStats();
	if (aaStats != nullptr) {
		DmgBuff = new AAStatsParamModif_Mul(AAStatType::Damage, 10);

		aaStats->AddModifier(*DmgBuff);
	}
}
DBG_ImmortalArmy::Immortality::~Immortality() {

	auto stats = &BuffsOwner.GetBattleStats();
	auto aaStats = stats->GetCurrAAStats();
	if (aaStats != nullptr) {

		aaStats->RemoveModifier(*DmgBuff);

		delete DmgBuff;
	}
}
DBG_ImmortalArmy::Immortality::Immortality(Entity& BuffsOwner, const AAStatsParamModif_Mul* DmgBuff) 
	:BuffsOwner(BuffsOwner),
	DmgBuff(DmgBuff){

}

bool DBG_ImmortalArmy::CheckImmDealCondition(Entity& entity) {
	return FractionsSystem::GetRelationToPlayer(entity.GetFraction()) == Relation::Ally;
}

void DBG_ImmortalArmy::TurnOn() {

	if (IsActive)
		return;

	auto it = EntitiesObserver::GetBeginIter();
	auto end = EntitiesObserver::GetAfterEndIter();
	Entity* ent = nullptr;
	for (;it != end;++it) {
		ent = *it;
		if (CheckImmDealCondition(*ent)) {
			Buffs.push_back(new Immortality(*ent));
		}
	}
	EntitiesObserver::AddEntityEvent.Add(AddAction);
	EntitiesObserver::RemoveEntityEvent.Add(RemAction);
	EntitiesObserver::UnloadEntitiesEvent.Add(UnloadAction);

	IsActive = true;
}
void DBG_ImmortalArmy::TurnOff() {

	if (!IsActive)
		return;

	for (auto imm : Buffs)
		delete imm;
	Buffs.clear();
	EntitiesObserver::AddEntityEvent.Remove(AddAction);
	EntitiesObserver::RemoveEntityEvent.Remove(RemAction);
	EntitiesObserver::UnloadEntitiesEvent.Remove(UnloadAction);
	
	IsActive = false;
}
void DBG_ImmortalArmy::OnAddEntityAction::Execute(Entity& args){

	if (CheckImmDealCondition(args)) {
		Buffs.push_back(new Immortality(args));
	}
}
void DBG_ImmortalArmy::OnRemoveEntityAction::Execute(Entity& args) {
	if (CheckImmDealCondition(args)) {
		FindImmByEntPredicate predicate(args);
		auto imm = CollectionsExts::Get(Buffs, predicate);
		delete imm;
		CollectionsExts::RemoveByPred(Buffs, predicate);
	}
}
void DBG_ImmortalArmy::OnUnloadEntitiesAction::Execute() {
	for (auto imm : Buffs)
		delete imm;
	Buffs.clear();
}