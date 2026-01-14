
#include <GameEff_Dur_EntBatStatMult.h>
#include <OrdersExecutor.h>

using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

GameEff_Dur_EntBatStatMult::GameEff_Dur_EntBatStatMult(EntityBattleStatType StatType, float MultValue)
	:StatType(StatType),
	MultValue(MultValue){

}
GameEff_Dur_EntBatStatMult::GameEff_Dur_EntBatStatMult(const GameEff_Dur_EntBatStatMult& copy)
	:StatType(copy.StatType),
	MultValue(copy.MultValue){

}
GameEff_Dur_EntBatStatMult::~GameEff_Dur_EntBatStatMult() {

}
IGameEffect& GameEff_Dur_EntBatStatMult::Clone() const {
	return *new GameEff_Dur_EntBatStatMult(*this);
}

void GameEff_Dur_EntBatStatMult::Activate(IGameEffTarget& target) {
	auto parTar = dynamic_cast<OrdersExecutor*>(&target);
	if (parTar != nullptr) {

		ParamMod = new BatStatsParamModif_Mul(StatType, MultValue);
		parTar->GetBattleStats().AddModifier(*ParamMod);
	}
}
void GameEff_Dur_EntBatStatMult::Dectivate(IGameEffTarget& target) {

	if (ParamMod != nullptr) {

		auto parTar = dynamic_cast<OrdersExecutor*>(&target);
		parTar->GetBattleStats().RemoveModifier(*ParamMod);
	}
}