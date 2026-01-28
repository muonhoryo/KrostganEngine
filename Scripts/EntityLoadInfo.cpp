
#include <WorldObjectLoadInfo.h>
#include <WorldObjsCatalogSerConsts.h>
#include <WorldObjsCatalog.h>
#include <Engine.h>

using namespace KrostganEngine::GameObjects;

bool EntityLoadInfo::WriteParam(Attr& param) {

	if (GameObjectLoadInfo::WriteParam(param)) {
		return true;
	}

	if (CheckParamName(param, WorldObjsLoad_ParamDefNames::ENTITY_FRACTION)) {
		string buffer = param.second;
		FStreamExts::ClearPath(buffer);
		FStreamExts::ToLowerStr(buffer);
		EntityFraction = FractionsSystem::GetFractionByName(buffer);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::ENTITY_HPBAR_SPRITE_SOURCE)) {
		HPBarSpriteSource = param.second;
		FStreamExts::ClearPath(HPBarSpriteSource);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::ENTITY_HPBAR_MASK)) {
		HPBarMaskSource = param.second;
		FStreamExts::ClearPath(HPBarMaskSource);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::ATTBLEOBJ_HITEFF_SPRITE_SOURCE)) {
		HitEffectSprite = param.second;
		FStreamExts::ClearPath(HitEffectSprite);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::ENTITY_SELECT_AREA_SOURCE)) {
		SelectionAreaSource = param.second;
		FStreamExts::ClearPath(SelectionAreaSource);
	}
	else {
		return false;
	}
	return true;
}
bool EntityLoadInfo::WriteParamByNode(xml_node<>& node) {

	if (WorldObjectLoadInfo::WriteParamByNode(node))
		return false;

	char* nodeName = node.name();

	if (nodeName == WorldObjsLoad_XMLChildrenType::AASTATS) {

		auto indexAtt = node.first_attribute();
		int index = -1;
		if (indexAtt->name() == WorldObjsLoad_ParamDefNames::AASTATS_INDEX) {

			index = stoi(indexAtt->value());
		}
		if (index == -1)
			index = BattleStats.AddAAStats(*new AutoAttackStats());
		else
			BattleStats.AddAAStatsByIndex(*new AutoAttackStats(), index);

		BattleStats.SetAAStats(index);
		auto stats = BattleStats.GetCurrAAStats();
		WriteBattleStatsParams(node, *stats);
		BattleStats.SetAAStats(0);
	}
	else if (nodeName == WorldObjsLoad_XMLChildrenType::BATSTATS) {

		WriteBattleStatsParams(node, BattleStats);
	}
	else if (nodeName == WorldObjsLoad_XMLChildrenType::ABILITY) {

		WriteAbility(node);
	}
	else
		return false;

	return true;
}

EntityLoadInfo::EntityLoadInfo(const EntityLoadInfo& copy)
	:GameObjectLoadInfo(copy),
		HPBarSpriteSource(copy.HPBarSpriteSource),
		HPBarMaskSource(copy.HPBarMaskSource),
		HitEffectSprite(copy.HitEffectSprite),
		SelectionAreaSource(copy.SelectionAreaSource),
		EntityFraction(copy.EntityFraction){

	copy.BattleStats.CopyTo(BattleStats);
	CollectionsExts::Clone(copy.Abilities, Abilities);
}
void EntityLoadInfo::VerifyAAStatsExisting() {

	if (BattleStats.GetCurrAAStats() == nullptr) {

		auto index = BattleStats.AddAAStats(*new AutoAttackStats());
		BattleStats.SetAAStats(index);
	}
}
void EntityLoadInfo::WriteBattleStatsParams(const string& input, IModifiableStatsWrapper& stats) {

	size_t start = 0;
	size_t end = 0;
	Attr* param = nullptr;
	while (true) {
		end = input.find(ENTITY_BSTATS_PARAMS_SEP, start);
		if (end == string::npos) {
			param = WorldObjsCatalogDeserial::ParseParamLine(input.substr(start, input.length() - start));
			stats.WriteParam(*param);
			break;
		}
		else {
			param = WorldObjsCatalogDeserial::ParseParamLine(input.substr(start, end - start));
			stats.WriteParam(*param);
			start = end + ENTITY_BSTATS_PARAMS_SEP.length();
		}
	}
}
void EntityLoadInfo::WriteBattleStatsParams(const xml_node<>& input, IModifiableStatsWrapper& stats) {

	string attrName;
	string attrValue;
	Attr* param = nullptr;
	const xml_attribute<>* attr = input.first_attribute();
	while (attr != nullptr) {

		attrName = attr->name();
		attrValue = attr->value();
		param = new Attr(attrName, attrValue);
		stats.WriteParam(*param);

		attr = attr->next_attribute();
	}
}
void EntityLoadInfo::WriteAbility(const xml_node<>& input) {

	string attrName;
	string attrValue;
	Attr* param = nullptr;
	const xml_attribute<>* attr = input.first_attribute();
	size_t catalogID = EMPTY_CATALOG_ID;
	std::byte subcatID = ABSENT_SUB_CATALOG_ID;
	while (attr != nullptr) {

		attrName = attr->name();
		attrValue = attr->value();
		param = new Attr(attrName, attrValue);
		if (CheckParamName(*param, DEF_CATALOG_ID)) {
			catalogID = stoll(param->second);
		}
		else if (CheckParamName(*param, DEF_SUB_CATALOG_ID)) {
			subcatID = (std::byte)stoi(param->second);
		}

		attr = attr->next_attribute();
	}

	Abilities.push_back(pair<size_t, std::byte>(catalogID, subcatID));
}

void EntityLoadInfo::FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const {
	GameObjectLoadInfo::FillCtorParams(params, usedInfo);

	EntityCtorParams* parParams = static_cast<EntityCtorParams*>(&params);
	auto& parUsedInfo = *dynamic_cast<const EntityLoadInfo*>(&usedInfo);

	ExtGlRes_Sprite* selSpr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(parUsedInfo.SelectionAreaSource));
	ExtGlRes_Sprite* hpbarSpr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(parUsedInfo.HPBarSpriteSource));
	ExtGlRes_Texture* hpbarMask = dynamic_cast<ExtGlRes_Texture*>(ExternalGlobalResources::GetRes(parUsedInfo.HPBarMaskSource));
	ExtGlRes_Sprite* hitEffSpr = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(parUsedInfo.HitEffectSprite);
	auto hpBarShad = hpbarSpr->RenShader;

	parParams->HitEffectSprite = new SpriteRenderer
	(hitEffSpr->Tex,
		hitEffSpr->MaxSize < eps ? Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution : hitEffSpr->MaxSize,
		hitEffSpr->RenShader);
	parParams->HitEffectSprite->SetRendLayer((std::byte)40);
	parParams->BattleStats = new EntityBattleStats(parUsedInfo.BattleStats);
	parParams->EntityFraction = parUsedInfo.EntityFraction;
	parParams->SelectionSpriteSource = selSpr;
	parParams->HPBarSprite = new IndicatorFill(
		hpbarSpr->Tex,
		hpbarMask->Tex,
		*hpbarSpr->RenShader,
		hpbarSpr->MaxSize);
	parParams->HPBarSprite->SetGlobalPosition(params.GlobalPosition);
	parParams->HPBarSprite->SetGlobalScale_Sng(parParams->HPBarSprite->GetGlobalScale_Sng() * params.GlobalScale);
	CollectionsExts::Clone(Abilities, parParams->Abilities);
}