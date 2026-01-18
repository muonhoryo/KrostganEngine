
#include <GameEff_Dur_Disarm.h>
#include <OrdersExecutor.h>

using namespace KrostganEngine::GameObjects;

GameEff_Dur_Disarm::GameEff_Dur_Disarm()
	:GameEff_Dur_EntBatStatConst_bool(EntityBattleStatType::Disarmed,true){

}
GameEff_Dur_Disarm::GameEff_Dur_Disarm(const GameEff_Dur_Disarm& copy)
	:GameEff_Dur_EntBatStatConst_bool(copy){

}
GameEff_Dur_Disarm::~GameEff_Dur_Disarm() {

}

IGameEffect& GameEff_Dur_Disarm::Clone() const {
	return *new GameEff_Dur_Disarm(*this);
}

void GameEff_Dur_Disarm::Activate(IGameEffTarget& target) {
	auto parOwner = dynamic_cast<OrdersExecutor*>(&target);
	if (parOwner != nullptr) {

		AAStatsIndex = parOwner->GetBattleStats().GetCurrAAStatsIndex();
	}
	GameEff_Dur_EntBatStatConst_bool::Activate(target);
}
void GameEff_Dur_Disarm::Deactivate(IGameEffTarget& target) {
	GameEff_Dur_EntBatStatConst_bool::Deactivate(target);
	auto parOwner = dynamic_cast<OrdersExecutor*>(&target);
	if (parOwner != nullptr) {

		parOwner->GetBattleStats().SetAAStats(AAStatsIndex);
	}
}