
#include <WorldObjectLoadInfo.h>
#include <WorldObjsCatalogSerConsts.h>

using namespace KrostganEngine::GameObjects;

GameObjectLoadInfo::GameObjectLoadInfo(const GameObjectLoadInfo& copy)
	:WorldObjectLoadInfo(copy) {

	SpriteSource = copy.SpriteSource;
}
bool GameObjectLoadInfo::WriteParam(Attr& param) {

	if (WorldObjectLoadInfo::WriteParam(param))
		return true;

	if (CheckParamName(param, WorldObjsLoad_ParamDefNames::IMAGEUSR_SPRITE_SOURCE)) {
		SpriteSource = *new string(param.second);
		FStreamExts::ClearPath(SpriteSource);
	}
	else if (param.first == WorldObjsLoad_ParamDefNames::GAMEOBJ_ISSOLID_COLL) {
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
	params.CatalogID = usedInfo.CatalogID;
	params.SolidCollision = usedInfo.SolidCollision;
}