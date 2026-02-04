
#include <WorldObjectLoadInfo.h>
#include <WorldObjsCatalogSerConsts.h>
#include <Decoration.h>
#include <Engine.h>

using namespace KrostganEngine::GameObjects;

DecorationLoadInfo::DecorationLoadInfo(const DecorationLoadInfo& copy)
	:GameObjectLoadInfo(copy) {

	HitEffectSprite = copy.HitEffectSprite;
	CurrentHP = copy.CurrentHP;
	MaxHP = copy.MaxHP;
	IsTargetableForAA = copy.IsTargetableForAA;
	Collider = &copy.Collider->Clone();
}

bool DecorationLoadInfo::WriteParam(Attr& param) {
	if (GameObjectLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, WorldObjsLoad_ParamDefNames::ATTBLEOBJ_HITEFF_SPRITE_SOURCE)) {
		HitEffectSprite = param.second;
		FStreamExts::ClearPath(HitEffectSprite);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::DECOR_HP_CURRENT)) {

		CurrentHP = stol(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::DECOR_HP_MAX)) {

		MaxHP = stol(param.second);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::DECOR_ISTARGBLE_FORAA)) {

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

	if (nodeName == WorldObjsLoad_XMLChildrenType::COLLIDER) {

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

WorldObjectLoadInfo& DecorationLoadInfo::Clone() const {
	return *new DecorationLoadInfo(*this);
}
