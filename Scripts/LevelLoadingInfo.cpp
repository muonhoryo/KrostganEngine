
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
			CatalogSubID = (std::byte)stoi(subs);
			end = subInfoIndex - LVLSER_SUBINFO_SEPARATOR.length();
		}
		else
			end = serInfo.length();

		subStr = serInfo.substr(0, end);
		CatalogID = stol(subStr);
	}
	else {
		if (subInfoIndex != string::npos &&
			subInfoIndex < end) {		//Index is not part of additional params

			subInfoIndex += LVLSER_SUBINFO_SEPARATOR.length();
			string subs = serInfo.substr(subInfoIndex, end - subInfoIndex - 1);
			CatalogSubID = (std::byte)stoi(subs);
			end = subInfoIndex - LVLSER_SUBINFO_SEPARATOR.length();
		}

		size_t start = 0;
		size_t sepInd = 0;
		subStr = serInfo.substr(0, end);
		CatalogID = stol(subStr);
		start = end + LVLSER_ELEM_PARAMS_DEF.length();
		const pair<const string, const string>* param = nullptr;

		//Read additional params
		while (true) {
			end = serInfo.find(LVLSER_ELEM_PARAMS_DEF, start);
			sepInd = serInfo.find(ObjsCatalogDeserial::PAR_DEF_NAME_END_SYM, start);
			if (end == string::npos)
				break;
			param = new pair<const string, const string>(serInfo.substr(start, sepInd-start), serInfo.substr(sepInd + 1, serInfo.length() - sepInd));
			attrs.push_back(param);
			start = end + LVLSER_ELEM_PARAMS_DEF.length();
		}
		param = new pair<const string, const string>(serInfo.substr(start, sepInd- start), serInfo.substr(sepInd + 1, serInfo.length() - sepInd));
		attrs.push_back(param);
		if (attrs.size() != 0)
			AdditParams = new LvlObjAdditParams(attrs);
		else
			delete& attrs;
	}
}
void LvlObjInstantiationInfo::Deserialize(const xml_node<>& serInfo) {

	const xml_attribute<>* attr = nullptr;
	char* attrName = nullptr;
	attr = serInfo.first_attribute();
	AttrsCollectn& attrs = *new AttrsCollectn();
	const pair<const string, const string>* param = nullptr;
	string addParamName;
	string addParamValue;
	
	//Deserialize attributes
	while (attr != nullptr) {

		attrName = attr->name();
		if (attrName == SerializationParDefNames::OBJECT_CATALOG_ID) {

			CatalogID = stol(attr->value());
		}
		else if (attrName == SerializationParDefNames::OBJECT_SUB_CATALOG_ID) {

			CatalogSubID = (std::byte)stoi(attr->value());
		}
		else {

			addParamName = string(attrName);
			addParamValue = string(attr->value());
			param = new pair<const string, const string>(addParamName, addParamValue);
			attrs.push_back(param);
		}

		attr = attr->next_attribute();
	}

	
	if (attrs.size() != 0)
		AdditParams = new LvlObjAdditParams(attrs);
	else
		delete& attrs;
}

WorldTransfObj* LvlObjInstantiationInfo::InstantiateObj() const {

	auto& objInfo = ObjectsCatalog::GetObjectInfo(CatalogID);
	auto subInfo = ObjectsCatalog::GetSubObjInfo(CatalogID, CatalogSubID);
	return objInfo.InstantiateObject(subInfo, AdditParams);
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

vector<LvlObjInstantiationInfo*>* LvlObjInstantiationInfo::DeserializeRow(const xml_node<>& rootNode) {

	vector<LvlObjInstantiationInfo*>& deserRow = *new vector<LvlObjInstantiationInfo*>();
	
	LvlObjInstantiationInfo* instInfo = nullptr;
	const xml_node<>* ch = rootNode.first_node();
	while (ch != nullptr) {

		if (ch->name() != SerXMLObjChildrenTypes::CHILD)
			throw exception("In children field must be only children of object");

		instInfo = new LvlObjInstantiationInfo();

		instInfo->Deserialize(*ch);

		if (instInfo->CatalogID == ObjectsCatalog::EMPTY_CATALOG_ID)
			throw exception("Instantiation injo hasn't CatalogID");

		deserRow.push_back(instInfo);

		ch = ch->next_sibling();
	}

	if (deserRow.size() == 0) {

		delete& deserRow;
		return nullptr;
	}
	else
		return &deserRow;
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
	bool fromCache = isSub || isAddParm;
	if (fromCache)
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

	auto obj = InstantiateObject_Action(fromCache ? *Cache: *this);

	if (fromCache)
		Cache->InstantiateChildren(*obj);
	else
		InstantiateChildren(*obj);

	if (fromCache)
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
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_REND_WARFOG_ISHIDEN)){
		WarFog_IsHiden = FStreamExts::ParseBool(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_REND_WARFOG_ISSHOWED)) {
		WarFog_IsShowed = FStreamExts::ParseBool(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::OBJECT_REND_LATERENDER)) {
		LateRender = FStreamExts::ParseBool(param.second);
	}
	else {
		return false;
	}
	return true;
}
bool WorldObjectLoadInfo::WriteParamByNode(xml_node<>& node) {

	char* nodeName = node.name();

	if (nodeName == SerXMLObjChildrenTypes::CHILDREN) {

		ChildObjs.clear();
		auto info = LvlObjInstantiationInfo::DeserializeRow(node);
		for (auto in : *info) {
			ChildObjs.push_back(LvlObjInstantiationInfo(*in));
		}
	}
	else
		return false;

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
			obj->SetGlobalScale_Sng(parent.GetGlobalScale_Sng()*obj->GetLocalScale_Sng());
			obj->SetLocalRotation(parent.GetGlobalRotation()+obj->GetLocalRotation());
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
	else if (param.first == SerializationParDefNames::GAMEOBJ_ISSOLID_COLL) {
		SolidCollision = FStreamExts::ParseBool(param.second);
	}
	else
		return false;

	return true;
}

void GameObjectLoadInfo::FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const {

	ExtGlRes_Sprite* spr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(usedInfo.SpriteSource));

	params.BodySpriteSource = spr;

	params.GlobalPosition = usedInfo.Position;
	params.GlobalScale = usedInfo.Size;
	params.CatalogID = usedInfo.CatID;
	params.SolidCollision = usedInfo.SolidCollision;
}

//Entity

bool EntityLoadInfo::WriteParam(Attr& param) {
	
	if (GameObjectLoadInfo::WriteParam(param)) {
		return true;
	}

	if (CheckParamName(param,SerializationParDefNames::ENTITY_FRACTION)) {
		string buffer = param.second;
		FStreamExts::ClearPath(buffer);
		FStreamExts::ToLowerStr(buffer);
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
	else if (CheckParamName(param, SerializationParDefNames::ATTBLEOBJ_HITEFF_SPRITE_SOURCE)) {
		HitEffectSprite = param.second;
		FStreamExts::ClearPath(HitEffectSprite);
	}
	else if (CheckParamName(param,SerializationParDefNames::ENTITY_SELECT_AREA_SOURCE)) {
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

	if (nodeName == SerXMLObjChildrenTypes::AASTATS) {

		auto index = BattleStats.AddAAStats(*new AutoAttackStats());
		BattleStats.SetAAStats(index);
		auto stats = BattleStats.GetCurrAAStats();
		WriteBattleStatsParams(node, *stats);
		BattleStats.SetAAStats(0);
	}
	else if (nodeName == SerXMLObjChildrenTypes::BATSTATS) {

		WriteBattleStatsParams(node, BattleStats);
	}
	else
		return false;

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
			param = ObjsCatalogDeserial::ParseParamLine(input.substr(start, input.length() - start));
			stats.WriteParam(*param);
			break;
		}
		else {
			param = ObjsCatalogDeserial::ParseParamLine(input.substr(start, end - start));
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
	parParams->EntityFraction=parUsedInfo.EntityFraction;
	parParams->SelectionSpriteSource = selSpr;
	parParams->HPBarSprite = new IndicatorFill(
		hpbarSpr->Tex,
		hpbarMask->Tex,
		*hpbarSpr->RenShader,
		hpbarSpr->MaxSize);
	parParams->HPBarSprite->SetGlobalPosition(params.GlobalPosition);
	parParams->HPBarSprite->SetGlobalScale_Sng(parParams->HPBarSprite->GetGlobalScale_Sng() * params.GlobalScale);
}
//Unit

WorldTransfObj* UnitLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	UnitObjectCtorParams& params = *new UnitObjectCtorParams();
	FillCtorParams(params, *dynamic_cast<const GameObjectLoadInfo*>(&usedInfo));
	UnitObject* unit = new UnitObject(params);
	delete &params;

	return unit;
}
WorldObjectLoadInfo* UnitLoadInfo::CreateCacheInfo() const {
	return new UnitLoadInfo(*this);
}

//Hero

WorldTransfObj* HeroLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& params = *new HeroObjectCtorParams();
	FillCtorParams(params, *dynamic_cast<const GameObjectLoadInfo*>(&usedInfo));
	HeroObject* hero = new HeroObject(params);
	delete& params;

	return hero;
}
bool HeroLoadInfo::WriteParam(Attr& param) {
	return UnitLoadInfo::WriteParam(param);
}
WorldObjectLoadInfo* HeroLoadInfo::CreateCacheInfo() const {
	return new HeroLoadInfo(*this);
}

//Wall

WorldTransfObj* WallLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& parInfo = *dynamic_cast<const WallLoadInfo*>(&usedInfo);

	auto& params = *new GameObjectCtorParams();
	FillCtorParams(params, *dynamic_cast<const GameObjectLoadInfo*>(&usedInfo));
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

//Decoration

DecorationLoadInfo::DecorationLoadInfo(const DecorationLoadInfo& copy)
	:GameObjectLoadInfo(copy){

	HitEffectSprite = copy.HitEffectSprite;
	CurrentHP = copy.CurrentHP;
	MaxHP = copy.MaxHP;
	IsTargetableForAA = copy.IsTargetableForAA;
	Collider = &copy.Collider->Clone();
}

bool DecorationLoadInfo::WriteParam(Attr& param) {
	if (GameObjectLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, SerializationParDefNames::ATTBLEOBJ_HITEFF_SPRITE_SOURCE)) {
		HitEffectSprite = param.second;
		FStreamExts::ClearPath(HitEffectSprite);
	}
	else if (CheckParamName(param, SerializationParDefNames::DECOR_HP_CURRENT)) {

		CurrentHP = stol(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::DECOR_HP_MAX)) {

		MaxHP = stol(param.second);
	}
	else if (CheckParamName(param, SerializationParDefNames::DECOR_ISTARGBLE_FORAA)) {
		
		IsTargetableForAA = FStreamExts::ParseBool(param.second);
	}
	else
		return false;

	return true;
}

bool DecorationLoadInfo::WriteParamByNode(xml_node<>& node) {
	if (WorldObjectLoadInfo::WriteParamByNode(node))
		return true;

	char* nodeName = node.name();

	if (nodeName == SerXMLObjChildrenTypes::Collider) {

		if (Collider != nullptr)
			delete Collider;
		Collider = &ColliderDeserializer::DeserializeCollider(node);
	}
	else
		return false;

	return true;
}

void DecorationLoadInfo::FillCtorParams(GameObjectCtorParams& params, const GameObjectLoadInfo& usedInfo) const {

	GameObjectLoadInfo::FillCtorParams(params, usedInfo);

	auto parParams = static_cast<DecorationCtorParams*>(&params);
	auto parUsedInfo = dynamic_cast<const DecorationLoadInfo*>(&usedInfo);

	ExtGlRes_Sprite* hitEffSpr = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(parUsedInfo->HitEffectSprite);

	parParams->HitEffectSprite = new SpriteRenderer
	(hitEffSpr->Tex,
		hitEffSpr->MaxSize < eps ? Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution : hitEffSpr->MaxSize,
		hitEffSpr->RenShader);
	parParams->HitEffectSprite->SetRendLayer((std::byte)40);
	parParams->CurrentHP = parUsedInfo->CurrentHP;
	parParams->MaxHP = parUsedInfo->MaxHP;
	parParams->Collider = &Collider->Clone();
}

WorldTransfObj* DecorationLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& parInfo = *dynamic_cast<const DecorationLoadInfo*>(&usedInfo);

	auto& params = *new DecorationCtorParams();
	FillCtorParams(params, *dynamic_cast<const GameObjectLoadInfo*>(&usedInfo));
	DecorationObject* decor = new DecorationObject(params);
	delete& params;

	return decor;
}

WorldObjectLoadInfo* DecorationLoadInfo::CreateCacheInfo() const {
	return new DecorationLoadInfo(*this);
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
		std::byte layer = (std::byte)stof(param.second);
		RendLayer = layer;
	}
	else if (CheckParamName(param, SerializationParDefNames::SPRITE_ORIGIN)) {
		Origin = ParseVec2f(param.second);
	}
	else
		return false;

	return true;
}
WorldTransfObj* SpriteRendLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& parInfo = *dynamic_cast<const SpriteRendLoadInfo*>(&usedInfo);

	auto src = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(parInfo.SpriteSource);
	auto sprt = new SpriteRenderer(src->Tex, parInfo.MaxSpriteSize < eps ? src->MaxSize : parInfo.MaxSpriteSize, src->RenShader);
	sprt->SetOrigin(Origin);
	sprt->SetGlobalPosition(parInfo.Position);
	sprt->SetGlobalRotation(parInfo.Rotation);
	sprt->SetGlobalScale_Sng(parInfo.Size * sprt->GetGlobalScale_Sng());
	sprt->SetRendLayer(RendLayer);
	sprt->Set_IsHidenByWarFog(WarFog_IsHiden);
	sprt->Set_IsShownByWarFog(WarFog_IsShowed);
	sprt->Set_LateRender(LateRender);

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