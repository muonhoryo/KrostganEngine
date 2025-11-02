
#include <LevelLoadingInfo.h>
#include <ObjectsCatalog.h>
#include <Extensions.h>
#include <RelationsSystem.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

//Gameobject

void GameObjectLoadInfo::ResetFromCache() {

	Name = Cache->Name;
	SpriteSource = Cache->SpriteSource;
	Position = Cache->Position;
	CatID = Cache->CatID;
	Size = Cache->Size;
}
bool GameObjectLoadInfo::WriteParam(Attr& param) {

	if (CheckParamName(param,SerializationParDefNames::OBJECT_NAME)) {
		Name = param.second;
	}
	else if (CheckParamName(param,SerializationParDefNames::OBJECT_CATALOG_ID)) {
		CatID = stol(param.second);
	}
	else if (CheckParamName(param,SerializationParDefNames::OBJECT_SPRITE_SOURCE)) {
		SpriteSource = *new string(param.second);
		FStreamExts::ClearPath(SpriteSource);
	}
	else if (CheckParamName(param,SerializationParDefNames::OBJECT_POSITION)) {
		Position = ParseVec2f(param.second);
	}
	else if (CheckParamName(param,SerializationParDefNames::OBJECT_SIZE)) {
		Size = stof(param.second);
	}
	else {
		return false;
	}
	return true;
}
bool GameObjectLoadInfo::CheckParamName(Attr& param, const string& paramName) {
	return param.first.find(paramName) != string::npos;
}

//Entity

bool EntityLoadInfo::WriteParam(Attr& param) {
	
	if (GameObjectLoadInfo::WriteParam(param)) {
		return true;
	}

	if (CheckParamName(param,SerializationParDefNames::ENTITY_FRACTION)) {
		string buffer = param.second;
		FStreamExts::ClearPath(buffer);
		if (FractionsSystem::FractionNames.find(buffer) == FractionsSystem::FractionNames.end())
			EntityFraction = Fraction::Neutral;
		else
			EntityFraction = FractionsSystem::FractionNames.at(buffer);
	}
	else if (CheckParamName(param,SerializationParDefNames::ENTITY_HPBAR_SPRITE_SOURCE)) {
		HPBarSpriteSource = param.second;
		FStreamExts::ClearPath(HPBarSpriteSource);
	}
	else if (CheckParamName(param,SerializationParDefNames::ENTITY_HPBAR_MASK)) {
		HPBarMaskSource = param.second;
		FStreamExts::ClearPath(HPBarMaskSource);
	}
	else if (CheckParamName(param,SerializationParDefNames::ENTITY_SELECT_AREA_SOURCE)) {
		SelectionAreaSource = param.second;
		FStreamExts::ClearPath(SelectionAreaSource);
	}
	//Fill battle stats
	else if (CheckParamName(param,SerializationParDefNames::UNIT_MOVINGSPEED)) {
		float s = stof(param.second);
		if (s >= 0)
			BattleStats.SetMovingSpeed(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_MAX_HP)) {
		size_t s = stol(param.second);
		if (s > 0)
			BattleStats.SetMaxHP(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_REGEN_HP_COUNT)) {
		size_t s = stol(param.second);
		BattleStats.SetHPRegenAmount(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_REGEN_HP_TICK)) {
		float s = stof(param.second);
		BattleStats.SetHPRegenTick(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_AA_DAMAGE)) {
		size_t s = stol(param.second);
		BattleStats.GetAAStats()->SetAADamage(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_AA_SPEED)) {
		float s = stof(param.second);
		BattleStats.GetAAStats()->SetAASpeed(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_AA_RANGE)) {
		float s = stof(param.second);
		BattleStats.GetAAStats()->SetAARange(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_AUTO_AGGR_RADIUS)) {
		float s = stof(param.second);
		BattleStats.SetAutoAggrRadius(s);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_ISRANGE)) {
		bool isRange = FStreamExts::ParseBool(param.second);
		BattleStats.GetAAStats()->SetIsRange(isRange);
	}
	else {
		return false;
	}
	return true;
}
void EntityLoadInfo::ResetFromCache() {
	
	GameObjectLoadInfo::ResetFromCache();
	
	EntityLoadInfo* parCache = dynamic_cast<EntityLoadInfo*>(Cache);
	HPBarSpriteSource = parCache->HPBarSpriteSource;
	HPBarMaskSource = parCache->HPBarMaskSource;
	SelectionAreaSource = parCache->SelectionAreaSource;
	EntityFraction = parCache->EntityFraction;
	parCache->BattleStats.CopyTo(BattleStats);
}

//Unit

GameObject* UnitLoadInfo::InstanceObject
		(LoadedObjects&			levInfo, 
		AttrsCollectn*			additParams,
		LvlObjCatalogSubInfo*	objSubInfo) {

	// ???Maybe it should be separate func, cause is used by three instance's in the same form???

	bool isSub = objSubInfo != nullptr;
	bool isAddParm = additParams != nullptr;
	if (isSub || isAddParm)
		Cache = new UnitLoadInfo(*this);	//Caching curr state during instantiating with overrided params

	if (isSub) {
		for (auto& par : objSubInfo->Attrs) {
			WriteParam(*par);
		}
	}
	if (isAddParm) {
		for (auto& par : *additParams) {
			WriteParam(*par);
		}
	}

	UnitObjectCtorParams& params = dynamic_cast<UnitObjectCtorParams&>(GetCtorParams());
	UnitObject* unit = new UnitObject(params);
	levInfo.LoadedUnits.push_front(unit);

	delete &params;

	if (isSub || isAddParm)
	{
		ResetFromCache();
		delete Cache;
	}

	return unit;
}

EntityCtorParams& UnitLoadInfo::GetCtorParams() {

	ExtGlRes_Sprite* spr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(SpriteSource));
	ExtGlRes_Sprite* selSpr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(SelectionAreaSource));
	ExtGlRes_Sprite* hpbarSpr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(HPBarSpriteSource));
	ExtGlRes_Texture* hpbarMask = dynamic_cast<ExtGlRes_Texture*>(ExternalGlobalResources::GetRes(HPBarMaskSource));
	auto hpBarShad = hpbarSpr->RenShader;

	UnitObjectCtorParams& params = *new UnitObjectCtorParams();

	params.BattleStats = new EntityBattleStats(BattleStats);
	params.SetFraction(EntityFraction);
	params.BodySpriteSource = spr;
	params.SelectionSpriteSource = selSpr;
	params.GlobalPosition = Position;
	params.GlobalScale = Size;
	params.HPBarSprite = new IndicatorFill(
		hpbarSpr->Tex,
		hpbarMask->Tex,
		*hpbarSpr->RenShader,
		hpbarSpr->MaxSize);
	params.HPBarSprite->SetGlobalPosition(params.GlobalPosition);
	params.HPBarSprite->SetGlobalScale_Sng(params.HPBarSprite->GetGlobalScale_Sng() * params.GlobalScale);
	params.CatalogID = CatID;

	return params;
}

//Hero

GameObject* HeroLoadInfo::InstanceObject(
	LoadedObjects&			levInfo, 
	AttrsCollectn*			additParams,
	LvlObjCatalogSubInfo*	objSubInfo) {

	bool isSub = objSubInfo != nullptr;
	bool isAdditParams = additParams != nullptr;
	if (isSub || isAdditParams)
		Cache = new HeroLoadInfo(*this);	//Caching curr state during instantiating with overrided params

	if (isSub) {
		for (auto& par : objSubInfo->Attrs) {
			WriteParam(*par);
		}
	}
	if (isAdditParams) {
		for (auto& par : *additParams) {
			WriteParam(*par);
		}
	}

	HeroObjectCtorParams& heParams = dynamic_cast<HeroObjectCtorParams&>(GetCtorParams());
	HeroObject* hero = new HeroObject(heParams);
	levInfo.LoadedUnits.push_front(hero);
	levInfo.LoadedHeroes.push_front(hero);

	delete& heParams;

	if (isSub || isAdditParams)
	{
		ResetFromCache();
		delete Cache;
	}

	return hero;
}
bool HeroLoadInfo::WriteParam(Attr& param) {
	return UnitLoadInfo::WriteParam(param);
}
EntityCtorParams& HeroLoadInfo::GetCtorParams() {
	
	UnitObjectCtorParams& uparams = dynamic_cast<UnitObjectCtorParams&>(UnitLoadInfo::GetCtorParams());
	HeroObjectCtorParams& hparams = *new HeroObjectCtorParams(uparams);
	delete& uparams;
	return hparams;
}

//Wall

GameObject* WallLoadInfo::InstanceObject(
	LoadedObjects&			levInfo, 
	AttrsCollectn*			additParams,
	LvlObjCatalogSubInfo*	objSubInfo) {

	bool isSub = objSubInfo != nullptr;
	bool isAddParm = additParams != nullptr;
	if (isSub || isAddParm)
		Cache = new WallLoadInfo(*this);	//Caching curr state during instantiating with overrided params

	if (isSub) {
		for (auto& par : objSubInfo->Attrs) {
			WriteParam(*par);
		}
	}
	if (isAddParm) {
		for (auto& par : *additParams) {
			WriteParam(*par);
		}
	}

	FStreamExts::ClearPath(SpriteSource);
	ExtGlRes_Sprite* spr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(SpriteSource));

	WallCtorParams& params = *new WallCtorParams();
	params.BodySpriteSource = spr;
	params.GlobalPosition = Position;
	params.GlobalScale = Size;
	WallObject* wall = new WallObject(params);
	delete &params;

	if (isSub || isAddParm) {

		ResetFromCache();
		delete Cache;
	}

	return wall;
}

bool WallLoadInfo::WriteParam(Attr& param) {
	return GameObjectLoadInfo::WriteParam(param);
}