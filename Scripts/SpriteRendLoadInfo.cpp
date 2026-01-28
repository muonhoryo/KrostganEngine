
#include <WorldObjectLoadInfo.h>
#include <WorldObjsCatalogSerConsts.h>
#include <Engine.h>

using namespace KrostganEngine::GameObjects;

SpriteRendLoadInfo::SpriteRendLoadInfo(const SpriteRendLoadInfo& copy)
	:WorldObjectLoadInfo(copy) {

	SpriteSource = copy.SpriteSource;
	MaxSpriteSize = copy.MaxSpriteSize;
	RendLayer = copy.RendLayer;
}
bool SpriteRendLoadInfo::WriteParam(Attr& param) {

	if (WorldObjectLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, WorldObjsLoad_ParamDefNames::IMAGEUSR_SPRITE_SOURCE)) {
		SpriteSource = *new string(param.second);
		FStreamExts::ClearPath(SpriteSource);
	}
	else if (CheckParamName(param, WorldObjsLoad_ParamDefNames::IMAGEUSR_SPRITE_LAYER)) {
		std::byte layer = (std::byte)stof(param.second);
		RendLayer = layer;
	}
	/*else if (CheckParamName(param, WorldObjsLoad_ParamDefs::SPRITE_ORIGIN)) {
		Origin = ParseVec2f(param.second);
	}*/
	else
		return false;

	return true;
}
WorldTransfObj* SpriteRendLoadInfo::InstantiateObject_Action(const WorldObjectLoadInfo& usedInfo) const {

	auto& parInfo = *dynamic_cast<const SpriteRendLoadInfo*>(&usedInfo);

	auto src = ExternalGlobalResources::GetRes_t<ExtGlRes_Sprite>(parInfo.SpriteSource);
	auto sprt = new SpriteRenderer(src->Tex, parInfo.MaxSpriteSize < eps ? src->MaxSize : parInfo.MaxSpriteSize, src->RenShader);
	//sprt->SetOrigin(Origin);
	sprt->SetGlobalPosition(parInfo.Position);
	sprt->SetGlobalRotation(parInfo.Rotation);
	sprt->SetGlobalScale_Sng(parInfo.Size * sprt->GetGlobalScale_Sng());
	sprt->SetRendLayer(RendLayer);
	sprt->Set_IsHidenByWarFog(WarFog_IsHiden);
	sprt->Set_IsShownByWarFog(WarFog_IsShowed);
	sprt->Set_LateRender(LateRender);

	return sprt;
}
WorldObjectLoadInfo& SpriteRendLoadInfo::Clone() const {
	return *new SpriteRendLoadInfo(*this);
}