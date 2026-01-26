
#include <ComposeGameEffectLoadInfo.h>
#include <GameEffectsCatalog.h>
#include <GameEffectsCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEffectLoadInfo_Periodical::ComposeGameEffectLoadInfo_Periodical() {

}
ComposeGameEffectLoadInfo_Periodical::ComposeGameEffectLoadInfo_Periodical(const ComposeGameEffectLoadInfo_Periodical& copy)
	:ComposeGameEffectLoadInfo_Temporal(copy),
		TickGameEff_CatalogID(copy.TickGameEff_CatalogID),
		TickGameEff_SubCatalogID(copy.TickGameEff_SubCatalogID),
		TickTime(copy.TickTime){

}
ComposeGameEffectLoadInfo_Periodical::~ComposeGameEffectLoadInfo_Periodical() {

}

ComposeGameEffect& ComposeGameEffectLoadInfo_Periodical::InstantiateGameEff() const {

	auto& tickEff = GameEffectsCatalog::GetObjectInfo(TickGameEff_CatalogID, TickGameEff_SubCatalogID).InstantiateGameEff();
	auto& eff = *new ComposeGameEff_Periodical
		(*dynamic_cast<ComposeGameEff_Instant*>(&tickEff),
		TickTime,
		EffTime,
		CatalogID,
		SubCatalogID);

	for (auto genEff : GeneralGameEffects_Dur) {
		eff.AddGameEffect_Durable(*genEff);
	}
	for (auto genEff : GeneralGameEffects_TimeDep) {
		eff.AddGameEffect_TimeDepended(*genEff);
	}
	return eff;

}
ComposeGameEffectLoadInfo& ComposeGameEffectLoadInfo_Periodical::Clone() const {
	return *new ComposeGameEffectLoadInfo_Periodical(*this);
}
bool ComposeGameEffectLoadInfo_Periodical::WriteParam(Attr& param) {

	if (ComposeGameEffectLoadInfo_Temporal::WriteParam(param))
		return true;

	if (CheckParamName(param, GameEffLoad_ParamDefNames::EFFECT_PERIOD_TICK_CATALOG_ID)) {

		TickGameEff_CatalogID = stoll(param.second);
	}
	else if (CheckParamName(param, GameEffLoad_ParamDefNames::EFFECT_PERIOD_TICK_SUBCATALOG_ID)) {

		TickGameEff_SubCatalogID = (std::byte)stoi(param.second);
	}
	else if (CheckParamName(param, GameEffLoad_ParamDefNames::EFFECT_PERIOD_TICK_TIME)) {

		TickTime = stof(param.second);
	}
	else
		return false;

	return true;
}