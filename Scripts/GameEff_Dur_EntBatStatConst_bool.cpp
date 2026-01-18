
#include <GameEff_Dur_EntBatStatConst_bool.h>
#include <OrdersExecutor.h>

using namespace KrostganEngine::GameObjects;

GameEff_Dur_EntBatStatConst_bool::GameEff_Dur_EntBatStatConst_bool(EntityBattleStatType StatType, bool Value) 
	:StatType(StatType),
	Value(Value){

}
GameEff_Dur_EntBatStatConst_bool::GameEff_Dur_EntBatStatConst_bool(const GameEff_Dur_EntBatStatConst_bool& copy)
	:StatType(copy.StatType),
	Value(copy.Value){

}
GameEff_Dur_EntBatStatConst_bool::~GameEff_Dur_EntBatStatConst_bool() {

}

IGameEffect& GameEff_Dur_EntBatStatConst_bool::Clone() const {
	return *new GameEff_Dur_EntBatStatConst_bool(*this);
}

void GameEff_Dur_EntBatStatConst_bool::Activate(IGameEffTarget& target) {
	auto parTar = dynamic_cast<OrdersExecutor*>(&target);
	if (parTar != nullptr) {

		auto& batStat = parTar->GetBattleStats();
		if (*batStat.GetFieldRef_bool(StatType, true) != Value) {

			batStat.AddModifier_bool(StatType);
		}
	}
}
void GameEff_Dur_EntBatStatConst_bool::Deactivate(IGameEffTarget& target) {

	auto parTar = dynamic_cast<OrdersExecutor*>(&target);
	if (parTar != nullptr) {

		auto& batStat = parTar->GetBattleStats();
		if (*batStat.GetFieldRef_bool(StatType, true) != Value) {

			batStat.RemoveModifier_bool(StatType);
		}
	}
}