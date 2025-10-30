
#include <DBG_ImmortalArmy.h>
#include <EntitiesObserver.h>

using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;

bool DBG_ImmortalArmy::CheckImmDealCondition(Entity& entity) {
	return FractionsSystem::GetRelationToPlayer(entity.GetFraction()) == Relation::Ally;
}
void DBG_ImmortalArmy::SetImmortality(Entity& entity) {

	EntityBattleStats::ParamModifier_Mul* dmgBuff = new EntityBattleStats::ParamModifier_Mul(EntityBattleStats::StatType::AADamage, 10);
	EntityBattleStats* stats = &entity.GetBattleStats();
	stats->AddModifier(*dmgBuff);
	Buffs.push_back(Immortality(*dmgBuff, entity));
}
void DBG_ImmortalArmy::RemoveImmortality(Immortality& immort, bool remFromlist) {
	EntityBattleStats* stats = &immort.BuffsOwner.GetBattleStats();
	stats->RemoveModifier(immort.DmgBuff);
	if (remFromlist)
		CollectionsExts::Remove(Buffs, immort);
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
			SetImmortality(*ent);
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

	EntityBattleStats* stats = nullptr;
	for (auto& imm : Buffs) {
		RemoveImmortality(imm);
	}
	Buffs.clear();
	EntitiesObserver::AddEntityEvent.Remove(AddAction);
	EntitiesObserver::RemoveEntityEvent.Remove(RemAction);
	EntitiesObserver::UnloadEntitiesEvent.Remove(UnloadAction);
	
	IsActive = false;
}
void DBG_ImmortalArmy::OnAddEntityAction::Execute(Entity& args){

	if (CheckImmDealCondition(args)) {
		SetImmortality(args);
	}
}
void DBG_ImmortalArmy::OnRemoveEntityAction::Execute(Entity& args) {
	if (CheckImmDealCondition(args)) {
		FindImmByEntPredicate predicate(args);
		RemoveImmortality(*CollectionsExts::Get(Buffs, predicate), true);
	}
}
void DBG_ImmortalArmy::OnUnloadEntitiesAction::Execute() {
	for (auto& imm : Buffs) {
		RemoveImmortality(imm);
	}
	Buffs.clear();
}