
#include <Ability_NonTar_TempEff.h>

using namespace KrostganEngine::GameObjects;

Ability_NonTar_TempEff::Ability_NonTar_TempEff(ComposeGameEff_Temporal& GameEff, float EffDuration, size_t CatalogID, std::byte SubcatalogID) 
	:Ability_NonTargetable(CatalogID,SubcatalogID),
		GameEff(GameEff),
		EffDuration(EffDuration){

}
Ability_NonTar_TempEff::Ability_NonTar_TempEff(ComposeGameEff_Temporal& GameEff, float EffDuration) 
	:GameEff(GameEff),
	EffDuration(EffDuration){

}
Ability_NonTar_TempEff::~Ability_NonTar_TempEff() {

}

void Ability_NonTar_TempEff::Activate(){

	auto parOwner = dynamic_cast<IGameEffTarget*>(Owner);
	if (parOwner != nullptr) {

		auto cpy = reinterpret_cast<ComposeGameEff_Temporal*>(&GameEff.Clone());
		cpy->SetEffectTime(EffDuration);
		parOwner->AddGameEff(*cpy);
	}
}