
#include <LevelLoadingInfo.h>
#include <ObjectsCatalog.h>
#include <Extensions.h>
#include <RelationsSystem.h>
#include <LevelManager.h>
#include <AutoAttackProjectiles.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

LvlObjInstantiationInfo::LvlObjInstantiationInfo()
	:CatalogID(ObjectsCatalog::EMPTY_CATALOG_ID),
	CatalogSubID(ObjectsCatalog::ABSENT_SUB_CATALOG_ID)
{}

void LvlObjInstantiationInfo::Deserialize(const string& serInfo) {

	if (serInfo.length() == 0)
		return;

	AttrsCollectn& attrs = *new AttrsCollectn();
	size_t subInfoIndex = serInfo.find(LVLSER_SUBINFO_SEPARATOR);
	size_t end = serInfo.find(LVLSER_ELEM_PARAMS_DEF);
	string subStr;
	if (end == string::npos) {		//Haven't additional params
		if (subInfoIndex != string::npos) {
			subInfoIndex += LVLSER_SUBINFO_SEPARATOR.length();
			string subs = serInfo.substr(subInfoIndex, serInfo.length() - subInfoIndex);
			CatalogSubID = (byte)stoi(subs);
			end = subInfoIndex - LVLSER_SUBINFO_SEPARATOR.length()-1;
		}
		else
			end = serInfo.length()-1;

		subStr = serInfo.substr(0, end - 1);
		CatalogID = stoi(serInfo);
	}
	else {
		if (subInfoIndex != string::npos) {
			subInfoIndex += LVLSER_SUBINFO_SEPARATOR.length();
			string subs = serInfo.substr(subInfoIndex, end - subInfoIndex - 2);
			CatalogSubID = (byte)stoi(subs);
			end = subInfoIndex - LVLSER_SUBINFO_SEPARATOR.length() - 1;
		}
		else
			end -= 1;

		size_t start = 0;
		size_t sepInd = 0;
		subStr = serInfo.substr(0, end - 1);
		CatalogID = stoi(subStr);
		start = end + LVLSER_ELEM_PARAMS_DEF.length()+1;
		const pair<const string, const string>* param = nullptr;

		//Read additional params
		while (true) {
			end = serInfo.find(LVLSER_ELEM_PARAMS_DEF, start);
			sepInd = serInfo.find(ObjsCatalogDeserial::PAR_DEF_NAME_END_SYM, start);
			if (end == string::npos)
				break;
			subStr = serInfo.substr(start, end - 1);
			param = new pair<const string, const string>(subStr.substr(start, sepInd), subStr.substr(sepInd + 1, subStr.length() - sepInd));
			attrs.push_back(param);
			start = end + LVLSER_ELEM_PARAMS_DEF.length();
		}
		subStr = serInfo.substr(start, serInfo.length() - start);
		param = new pair<const string, const string>(subStr.substr(start, sepInd), subStr.substr(sepInd + 1, subStr.length() - sepInd));
		attrs.push_back(param);
		if (attrs.size() != 0)
			AdditParams = new LvlObjAdditParams(attrs);
		else
			delete& attrs;
	}
}
WorldTransfObj* LvlObjInstantiationInfo::InstantiateObj() const {

	auto objInfo = ObjectsCatalog::GetObjectInfo(CatalogID);
	auto subInfo = ObjectsCatalog::GetSubObjInfo(CatalogID, CatalogSubID);
	return objInfo->InstantiateObject(subInfo, AdditParams);
}

vector<LvlObjInstantiationInfo*>* LvlObjInstantiationInfo::DeserializeRow(const string& row) {
	
	if (row.length() == 0)
		return nullptr;
	vector<LvlObjInstantiationInfo*>& deserRow = *new vector<LvlObjInstantiationInfo*>();
	size_t start = 0;
	size_t end = 0;
	LvlObjInstantiationInfo* celInf = nullptr;
	string elStr;
	while (true) {
		end = row.find(LVLSER_ELEM_ROW_SEPARATOR, start);
		if (end ==string::npos) {
			break;
		}

		elStr = row.substr(start, end - start);
		celInf = new LvlObjInstantiationInfo();
		celInf->Deserialize(elStr);
		if (celInf != nullptr)
			deserRow.push_back(celInf);
		start = end + LVLSER_ELEM_ROW_SEPARATOR.length();
	}
	elStr = row.substr(start, row.length() - start);
	celInf = new LvlObjInstantiationInfo();
	celInf->Deserialize(elStr);
	if (celInf->CatalogID!=ObjectsCatalog::EMPTY_CATALOG_ID)
		deserRow.push_back(celInf);

	if (deserRow.size() > 0)
		return &deserRow;
	else
	{
		delete& deserRow;
		return nullptr;
	}
}

//WorldObjectLoadInfo

WorldObjectLoadInfo::WorldObjectLoadInfo(const WorldObjectLoadInfo& copy) {
	Name = copy.Name;
	Position = copy.Position;
	Size = copy.Size;
	Rotation = copy.Rotation;
	CatID = copy.CatID;
	ChildObjs = vector<LvlObjInstantiationInfo>(copy.ChildObjs);

	Cache = nullptr;
}

WorldTransfObj* WorldObjectLoadInfo::InstantiateObject
	(LvlObjAdditParams* objSubInfo,
	LvlObjAdditParams* additParams) const {

	// ???Maybe it should be separate func, cause is used by three instance's in the same form???

	bool isSub = objSubInfo != nullptr;
	bool isAddParm = additParams != nullptr;
	if (isSub || isAddParm)
		Cache = CreateCacheInfo();

	if (isSub) {
		for (auto par : objSubInfo->Attrs) {
			Cache->WriteParam(*par);
		}
	}
	if (isAddParm) {
		for (auto par : additParams->Attrs) {
			Cache->WriteParam(*par);
		}
	}

	auto obj = InstantiateObject_Action((isSub || isAddParm)? *Cache: *this);

	InstantiateChildren(*obj);

	if (isSub || isAddParm)
	{
		delete Cache;
	}
	LevelManager::InstantiateObjEvHandler.Execute(obj);
	return obj;
}

bool WorldObjectLoadInfo::WriteParam(Attr& param) {

	if (CheckParamName(param, SerializationParDefNames::OBJECT_NAME)) {
		Name = param.second;
	}
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_CATALOG_ID)) {
		CatID = stol(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_ROTATION)) {
		Rotation = stof(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_POSITION)) {
		Position = ParseVec2f(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_SIZE)) {
		Size = stof(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_CHILDREN)) {

		auto info = LvlObjInstantiationInfo::DeserializeRow(param.second);
		for (auto in : *info) {
			ChildObjs.push_back(LvlObjInstantiationInfo(*in));
		}
	}
	else {
		return false;
	}
	return true;
}

bool WorldObjectLoadInfo::CheckParamName(Attr& param, const string& paramName) {
	return param.first==paramName;
}

void WorldObjectLoadInfo::InstantiateChildren(WorldTransfObj& parent) const {

	if (RecursionCount >= Engine::GetGlobalConsts().Instantiation_MaxDepthLvl) //Recursion overload check
		throw exception("Instantiating recursion overload");

	//Recursivly instantiate children
	if (ChildObjs.size() != 0) {
		++RecursionCount;

		WorldTransfObj* obj = nullptr;
		for (auto& ch : ChildObjs) {

			obj = ch.InstantiateObj();
			obj->SetParent(&parent);
			obj->SetLocalPosition(DEFAULT_POSITION);
			obj->SetLocalScale_Sng(DEFAULT_SCALE_SNG);
			obj->SetLocalRotation(0);
		}
		--RecursionCount;
	}
}

//Gameobject

GameObjectLoadInfo::GameObjectLoadInfo(const GameObjectLoadInfo& copy)
	:WorldObjectLoadInfo(copy){

	SpriteSource = copy.SpriteSource;
}
bool GameObjectLoadInfo::WriteParam(Attr& param) {

	if (WorldObjectLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, SerializationParDefNames::IMAGEUSR_SPRITE_SOURCE)) {
		SpriteSource = *new string(param.second);
		FStreamExts::ClearPath(SpriteSource);
	}
	else
		return false;

	return true;
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
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_HITEFF_SPRITE_SOURCE)) {
		HitEffectSprite = param.second;
		FStreamExts::ClearPath(HitEffectSprite);
	}
	else if (CheckParamName(param,SerializationParDefNames::ENTITY_SELECT_AREA_SOURCE)) {
		SelectionAreaSource = param.second;
		FStreamExts::ClearPath(SelectionAreaSource);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_BATTLE_STATS)) {
		WriteBattleStatsParams(param.second, BattleStats);
	}
	else if (CheckParamName(param, SerializationParDefNames::ENTITY_AA_STATS)) {

		auto index = BattleStats.AddAAStats(*new AutoAttackStats());
		BattleStats.SetAAStats(index);
		auto stats = BattleStats.GetCurrAAStats();
		WriteBattleStatsParams(param.second, *stats);
		BattleStats.SetAAStats(0);
	}
	////Fill battle stats
	//else if (CheckParamName(param, EntityBattleStats::StatToStr(EntityBattleStatType::MaxHP))) {
	//	size_t s = stol(param.second);
	//	if (s > 0)
	//		BattleStats.SetMaxHP(s);
	//}
	//else if (CheckParamName(param, EntityBattleStats::StatToStr(EntityBattleStatType::RegenHP_Amount))) {
	//	size_t s = stol(param.second);
	//	BattleStats.SetHPRegenAmount(s);
	//}
	//else if (CheckParamName(param, EntityBattleStats::StatToStr(EntityBattleStatType::MovingSpeed))) {
	//	float s = stof(param.second);
	//	BattleStats.SetMovingSpeed(s);
	//}
	//else if (CheckParamName(param, EntityBattleStats::StatToStr(EntityBattleStatType::RegenHP_Tick))) {
	//	float s = stof(param.second);
	//	BattleStats.SetHPRegenTick(s);
	//}
	//else if (CheckParamName(param, EntityBattleStats::StatToStr(EntityBattleStatType::AutoAggrRadius))) {
	//	float s = stof(param.second);
	//	BattleStats.SetAutoAggrRadius(s);
	//}
	//else if (CheckParamName(param, EntityBattleStats::StatToStr(EntityBattleStatType::IsTargetableForAA))) {
	//	bool isTargetable= FStreamExts::ParseBool(param.second);
	//	BattleStats.SetTargetableForAA(isTargetable);
	//}
	////Fill AA-stats
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::Damage))) {
	//	VerifyAAStatsExisting();
	//	size_t s = stol(param.second);
	//	BattleStats.GetCurrAAStats()->SetDamage(s);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::Speed))) {
	//	VerifyAAStatsExisting();
	//	float s = stof(param.second);
	//	BattleStats.GetCurrAAStats()->SetSpeed(s);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::Range))) {
	//	VerifyAAStatsExisting();
	//	float s = stof(param.second);
	//	BattleStats.GetCurrAAStats()->SetRange(s);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::ProjSpeed))) {
	//	VerifyAAStatsExisting();
	//	float s = stof(param.second);
	//	BattleStats.GetCurrAAStats()->SetProjSpeed(s);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::SiegeRange))) {
	//	VerifyAAStatsExisting();
	//	float s = stof(param.second);
	//	BattleStats.GetCurrAAStats()->SetSiegeRange(s);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::IsRange))) {
	//	VerifyAAStatsExisting();
	//	bool isRange = FStreamExts::ParseBool(param.second);
	//	BattleStats.GetCurrAAStats()->SetIsRange(isRange);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::Proj_LockRotation))) {
	//	VerifyAAStatsExisting();
	//	bool lockRot = FStreamExts::ParseBool(param.second);
	//	BattleStats.GetCurrAAStats()->SetProj_LockRotation(lockRot);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::IsSiege))) {
	//	VerifyAAStatsExisting();
	//	bool isSiege = FStreamExts::ParseBool(param.second);
	//	BattleStats.GetCurrAAStats()->SetIsSiege(isSiege);
	//}
	//else if (CheckParamName(param, AutoAttackStats::StatToStr(AAStatType::Proj_IsSelfHoming))) {
	//	VerifyAAStatsExisting();
	//	bool isSelfHoming= FStreamExts::ParseBool(param.second);
	//	BattleStats.GetCurrAAStats()->SetProj_IsSelfHoming(isSelfHoming);
	//}
	else {
		return false;
	}
	return true;
}
EntityLoadInfo::EntityLoadInfo(const EntityLoadInfo& copy)
	:GameObjectLoadInfo(copy){

	HPBarSpriteSource = copy.HPBarSpriteSource;
	HPBarMaskSource = copy.HPBarMaskSource;
	HitEffectSprite = copy.HitEffectSprite;
	SelectionAreaSource = copy.SelectionAreaSource;
	EntityFraction = copy.EntityFraction;
	copy.BattleStats.CopyTo(BattleStats);
}
void EntityLoadInfo::VerifyAAStatsExisting() {
	
	if (BattleStats.GetCurrAAStats() == nullptr) {

		auto index= BattleStats.AddAAStats(*new AutoAttackStats());
		BattleStats.SetAAStats(index);
	}
}
void EntityLoadInfo::WriteBattleStatsParams(const string& input, IModifiableStatsWrapper& stats){

	size_t start = 0;
	size_t end = 0;
	Attr* param = nullptr;
	while (true) {
		end = input.find(ENTITY_BSTATS_PARAMS_SEP, start);
		if (end == string::npos) {
			param = ObjsCatalogDeserial::ParseParamLine(input.substr(start, input.length() - start ));
			stats.WriteParam(*param);
			break;
		}
		else {
			param = ObjsCatalogDeserial::ParseParamLine(input.substr(start, end - start - 1));
			stats.WriteParam(*param);
			start = end + ENTITY_BSTATS_PARAMS_SEP.length();
		}
	}
}
//Unit

WorldTransfObj* UnitLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	UnitObjectCtorParams& params = dynamic_cast<UnitObjectCtorParams&>(GetCtorParams(usedInfo));
	UnitObject* unit = new UnitObject(params);

	delete &params;

	return unit;
}
EntityCtorParams& UnitLoadInfo::GetCtorParams(const WorldObjectLoadInfo& usedInfo) const {

	auto& parUsedInfo = *dynamic_cast<const UnitLoadInfo*>(&usedInfo);

	ExtGlRes_Sprite* spr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(parUsedInfo.SpriteSource));
	ExtGlRes_Sprite* selSpr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(parUsedInfo.SelectionAreaSource));
	ExtGlRes_Sprite* hpbarSpr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(parUsedInfo.HPBarSpriteSource));
	ExtGlRes_Texture* hpbarMask = dynamic_cast<ExtGlRes_Texture*>(ExternalGlobalResources::GetRes(parUsedInfo.HPBarMaskSource));
	ExtGlRes_Sprite* hitEffSpr = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(parUsedInfo.HitEffectSprite);
	auto hpBarShad = hpbarSpr->RenShader;

	UnitObjectCtorParams& params = *new UnitObjectCtorParams();

	params.BattleStats = new EntityBattleStats(parUsedInfo.BattleStats);
	params.SetFraction(parUsedInfo.EntityFraction);
	params.BodySpriteSource = spr;
	params.SelectionSpriteSource = selSpr;
	params.HitEffectSprite = new SpriteRenderer
		(hitEffSpr->Tex,
		hitEffSpr->MaxSize < eps ? Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution : hitEffSpr->MaxSize,
		hitEffSpr->RenShader);
	params.GlobalPosition = parUsedInfo.Position;
	params.GlobalScale = parUsedInfo.Size;
	params.HPBarSprite = new IndicatorFill(
		hpbarSpr->Tex,
		hpbarMask->Tex,
		*hpbarSpr->RenShader,
		hpbarSpr->MaxSize);
	params.HPBarSprite->SetGlobalPosition(params.GlobalPosition);
	params.HPBarSprite->SetGlobalScale_Sng(params.HPBarSprite->GetGlobalScale_Sng() * params.GlobalScale);
	params.CatalogID = parUsedInfo.CatID;

	return params;
}
WorldObjectLoadInfo* UnitLoadInfo::CreateCacheInfo() const {
	return new UnitLoadInfo(*this);
}

//Hero

WorldTransfObj* HeroLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	HeroObjectCtorParams& heParams = dynamic_cast<HeroObjectCtorParams&>(GetCtorParams(usedInfo));
	HeroObject* hero = new HeroObject(heParams);

	delete& heParams;

	return hero;
}
bool HeroLoadInfo::WriteParam(Attr& param) {
	return UnitLoadInfo::WriteParam(param);
}
EntityCtorParams& HeroLoadInfo::GetCtorParams(const WorldObjectLoadInfo& usedInfo) const {
	
	UnitObjectCtorParams& uparams = dynamic_cast<UnitObjectCtorParams&>(UnitLoadInfo::GetCtorParams(usedInfo));
	HeroObjectCtorParams& hparams = *new HeroObjectCtorParams(uparams);
	delete& uparams;
	return hparams;
}
WorldObjectLoadInfo* HeroLoadInfo::CreateCacheInfo() const {
	return new HeroLoadInfo(*this);
}

//Wall

WorldTransfObj* WallLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& parInfo = *dynamic_cast<const WallLoadInfo*>(&usedInfo);

	string path = string(parInfo.SpriteSource);
	FStreamExts::ClearPath(path);
	ExtGlRes_Sprite* spr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(path));

	WallCtorParams& params = *new WallCtorParams();
	params.BodySpriteSource = spr;
	params.GlobalPosition = parInfo.Position;
	params.GlobalScale = parInfo.Size;
	WallObject* wall = new WallObject(params);
	delete &params;

	return wall;
}
bool WallLoadInfo::WriteParam(Attr& param) {
	return GameObjectLoadInfo::WriteParam(param);
}
WorldObjectLoadInfo* WallLoadInfo::CreateCacheInfo() const {
	return new WallLoadInfo(*this);
}

//SpriteRenderer

SpriteRendLoadInfo::SpriteRendLoadInfo(const SpriteRendLoadInfo& copy) 
	:WorldObjectLoadInfo(copy){

	SpriteSource = copy.SpriteSource;
	MaxSpriteSize = copy.MaxSpriteSize;
	RendLayer = copy.RendLayer;
}
bool SpriteRendLoadInfo::WriteParam(Attr& param) {

	if (WorldObjectLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, SerializationParDefNames::IMAGEUSR_SPRITE_SOURCE)) {
		SpriteSource = *new string(param.second);
		FStreamExts::ClearPath(SpriteSource);
	}
	else if (CheckParamName(param, SerializationParDefNames::IMAGEUSR_SPRITE_LAYER)) {
		byte layer = (byte)stof(param.second);
		RendLayer = layer;
	}
	else
		return false;

	return true;
}
WorldTransfObj* SpriteRendLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& parInfo = *dynamic_cast<const SpriteRendLoadInfo*>(&usedInfo);

	auto src = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(parInfo.SpriteSource);
	auto sprt = new SpriteRenderer(src->Tex, parInfo.MaxSpriteSize < eps ? src->MaxSize : parInfo.MaxSpriteSize, src->RenShader);
	sprt->SetGlobalPosition(parInfo.Position);
	sprt->SetGlobalRotation(parInfo.Rotation);
	sprt->SetGlobalScale_Sng(parInfo.Size);
	sprt->SetRendLayer(RendLayer);

	return sprt;
}
WorldObjectLoadInfo* SpriteRendLoadInfo::CreateCacheInfo() const {
	return new SpriteRendLoadInfo(*this);
}

//AAProjectileLoadInfo

AAProjectileLoadInfo::AAProjectileLoadInfo(const AAProjectileLoadInfo& copy)
	:WorldObjectLoadInfo(copy) {

	Target = copy.Target;
	Owner = copy.Owner;
}
AutoAttackProjectile& AAProjectileLoadInfo::InstantiateProjectile
	(AutoAttackModule& Owner,
	IAttackableObj& Target,
	LvlObjAdditParams* objSubInfo,
	LvlObjAdditParams* additParams) const {

	this->Owner = &Owner;
	this->Target = &Target;
	auto proj = InstantiateObject(objSubInfo, additParams);
	this->Owner = nullptr;
	this->Target = nullptr;
	return *dynamic_cast<AutoAttackProjectile*>(proj);
}
WorldTransfObj* AAProjectileLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	AutoAttackProjectile* proj = nullptr;
	auto aastats = Owner->GetCurrAAStats();
	if (aastats->GetState_IsSiege() && !aastats->GetState_Proj_IsSelfHoming()) {

		AAProjectileCtorParams_NoTar params = AAProjectileCtorParams_NoTar(*Owner, Target->GetGlobalPosition());
		params.CatalogID = CatID;
		params.GlobalPosition = Position;
		params.GlobalScale = Size;
		proj = new AAProj_NoTar(params);
	}
	else {
		auto& ptr = Target->GetPtr();
		AAProjectileCtorParams_TarDir params = AAProjectileCtorParams_TarDir(*Owner, ptr);
		params.CatalogID = CatID;
		params.GlobalPosition = Position;
		params.GlobalScale = Size;
		proj = new AAProj_TarDir(params);
		delete& ptr;
	}
	return proj;
}
WorldObjectLoadInfo* AAProjectileLoadInfo::CreateCacheInfo() const {
	return new AAProjectileLoadInfo(*this);
}