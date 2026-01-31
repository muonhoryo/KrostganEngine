
#include <GameEff_Dur_Deserter.h>
#include <LevelManager.h>
#include <VectExts.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

GameEff_Dur_Deserter::GameEff_Dur_Deserter(FractionWrapper DesertingFrac)
	:DesertingFrac(DesertingFrac),
	StatChangedSubs(StatChangedEvSubs(*this)){

}
GameEff_Dur_Deserter::GameEff_Dur_Deserter(const GameEff_Dur_Deserter& copy) 
	:IGameEffect_Durable(copy),
	DesertingFrac(copy.DesertingFrac),
	StatChangedSubs(StatChangedEvSubs(*this)),
	OwnedEff_CatID(copy.OwnedEff_CatID),
	OwnedEff_SubcatID(copy.OwnedEff_SubcatID){

}
GameEff_Dur_Deserter::~GameEff_Dur_Deserter() {

	if (FracChangedSubs != nullptr) {
		delete FracChangedSubs;
	}
}
IGameEffect& GameEff_Dur_Deserter::Clone() const {
	return *new GameEff_Dur_Deserter(*this);
}

void GameEff_Dur_Deserter::SetOwnedEffect(ComposeGameEff_Permanent& ownedEffect) {
	
	OwnedEff_CatID = ownedEffect.GetCatalogID();
	OwnedEff_SubcatID = ownedEffect.GetSubcatalogID();
}

void GameEff_Dur_Deserter::Activate(IGameEffTarget& target) {

	auto orExec = dynamic_cast<OrdersExecutor*>(&target);
	if (orExec == nullptr) {
		RemoveEff(target);
		return;
	}
	if (!CheckResistance(*orExec)) {
		RemoveEff(target);
		return;
	}
	auto fracMem = dynamic_cast<IFractionMember*>(&target);
	if (fracMem == nullptr) {
		RemoveEff(target);
		return;
	}
	Target = &target;
	OriginFrac = fracMem->GetFraction();
	fracMem->SetFraction(DesertingFrac);
	FracChangedSubs = new FractionChangedEvSubs(*fracMem, DesertingFrac);
	Vector2f center = LevelManager::GetCenterOfLevel();
	Vector2f dir = orExec->GetGlobalPosition() - center;
	dir = Normalize(dir);
	dir.x = dir.x * 1000;
	dir.y = dir.y * 1000;
	orExec->TryAddOrder(*new EntityOrder_MoveToPoint(*orExec, orExec->GetGlobalPosition() + dir));
	IFractionMember::MemberHasChangedFracEvent.Add(*FracChangedSubs);
	auto& batStats = orExec->GetBattleStats();
	batStats.DefaultStatChangedEvent.Add(StatChangedSubs);
	batStats.StatChangedEvent.Add(StatChangedSubs);
}
void GameEff_Dur_Deserter::Deactivate(IGameEffTarget& target) {

	if (FracChangedSubs != nullptr) {

		Target = nullptr;
		auto orExec = dynamic_cast<OrdersExecutor*>(&target);
		auto& batStats = orExec->GetBattleStats();
		auto fracMem = dynamic_cast<IFractionMember*>(&target);
		IFractionMember::MemberHasChangedFracEvent.Remove(*FracChangedSubs);
		batStats.DefaultStatChangedEvent.Remove(StatChangedSubs);
		batStats.StatChangedEvent.Remove(StatChangedSubs);
		fracMem->SetFraction(OriginFrac);
		delete FracChangedSubs;
		FracChangedSubs = nullptr;
	}
}
void GameEff_Dur_Deserter::RemoveEff(IGameEffTarget& target) {
	target.RemoveGameEffByID(OwnedEff_CatID, OwnedEff_SubcatID);
}
bool GameEff_Dur_Deserter::CheckResistance(OrdersExecutor& target) const {
	return target.GetBattleStats().GetResistance_MindAtt().Stat < 1;
}