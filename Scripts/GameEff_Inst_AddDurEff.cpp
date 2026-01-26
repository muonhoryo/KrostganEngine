
#include <GameEff_Inst_AddDurEff.h>
#include <GameEffectsCatalog.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

GameEff_Inst_AddDurEff::GameEff_Inst_AddDurEff(size_t AddedGameEff_CatalogID, std::byte	AddedGameEff_SubcatalogID)
	:AddedGameEff_CatalogID(AddedGameEff_CatalogID),
	AddedGameEff_SubcatalogID(AddedGameEff_SubcatalogID){

}
GameEff_Inst_AddDurEff::GameEff_Inst_AddDurEff(const GameEff_Inst_AddDurEff& copy) 
	:IGameEffect_Instant(copy),
		AddedGameEff_CatalogID(copy.AddedGameEff_CatalogID),
		AddedGameEff_SubcatalogID(copy.AddedGameEff_SubcatalogID){

}
GameEff_Inst_AddDurEff::~GameEff_Inst_AddDurEff() {

}

void GameEff_Inst_AddDurEff::Activate(IGameEffTarget& target) {

	ComposeGameEffectLoadInfo* addedGameEff = &GameEffectsCatalog::GetObjectInfo(AddedGameEff_CatalogID, AddedGameEff_SubcatalogID);

	if (addedGameEff->IsStackable ||
		!target.HasGameEffect(AddedGameEff_CatalogID, AddedGameEff_SubcatalogID)) {

		target.AddGameEff(addedGameEff->InstantiateGameEff());
	}
}

IGameEffect& GameEff_Inst_AddDurEff::Clone() const {
	return *new GameEff_Inst_AddDurEff(*this);
}