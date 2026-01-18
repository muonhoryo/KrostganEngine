
#include <GameEff_Inst_AddDurEff.h>

using namespace KrostganEngine::GameObjects;

GameEff_Inst_AddDurEff::GameEff_Inst_AddDurEff(ComposeGameEff_Permanent& AddedGameEff)
	:AddedGameEff(AddedGameEff){

}
GameEff_Inst_AddDurEff::GameEff_Inst_AddDurEff(const GameEff_Inst_AddDurEff& copy) 
	:IGameEffect_Instant(copy),
	AddedGameEff(copy.AddedGameEff){

}
GameEff_Inst_AddDurEff::~GameEff_Inst_AddDurEff() {

}

void GameEff_Inst_AddDurEff::Activate(IGameEffTarget& target) {

	if (AddedGameEff.Get_IsStackable() ||
		!target.HasGameEffect(AddedGameEff.GetCatalogID(),AddedGameEff.GetSubcatalogID())) {

		target.AddGameEff(AddedGameEff.Clone());
	}
}

IGameEffect& GameEff_Inst_AddDurEff::Clone() const {
	return *new GameEff_Inst_AddDurEff(*this);
}