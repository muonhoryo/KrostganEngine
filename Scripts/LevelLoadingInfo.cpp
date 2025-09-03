
#include <LevelLoadingInfo.h>
#include <ObjectsCatalog.h>
#include <Extensions.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

GameObject* UnitLoadInfo::InstanceObject(LoadedObjects& levInfo, Vector2f position, vector<string>* additParams) {

	UnitObjectCtorParams& params = GetUnitParams();
	string* output = new string();
	if (additParams!=nullptr && 
		ObjsCatalogDeserial::TryGetSerValueOfParam(*additParams, SerializationParDefNames::OBJECT_POSITION, output)) {
		params.GlobalPosition = ParseVec2f(*output);
	}
	else {
		params.GlobalPosition = position;
	}

	UnitObject* unit = new UnitObject(params);
	levInfo.LoadedUnits.push_front(unit);
	//levInfo.LoadedGraphics.push_front(unit);

	delete output;
	delete &params;

	return unit;
}

UnitObjectCtorParams& UnitLoadInfo::GetUnitParams() {

	FStreamExts::ClearPath(SpriteSource);

	ExtGlRes_Sprite* spr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(SpriteSource));
	ExtGlRes_Sprite* selSpr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(SelectionAreaSource));
	ExtGlRes_Sprite* hpbarSpr= dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(HPBarSpriteSource));
	ExtGlRes_Texture* hpbarMask= dynamic_cast<ExtGlRes_Texture*>(ExternalGlobalResources::GetRes(HPBarMaskSource));
	auto hpBarShad = hpbarSpr->RenShader;

	UnitObjectCtorParams& params = *new UnitObjectCtorParams();

	params.BattleStats		=	new EntityBattleStats(*BattleStats);
	params.EntityFraction	=	EntityFraction;
	params.RenSprite		=	spr;
	params.SelectionSprite	=	selSpr;
	params.GlobalPosition			=	Position;
	params.LocalScale				=	Size;
	params.HPBarSprite		=	new IndicatorFill(
									hpbarSpr->Tex,
									hpbarMask->Tex, 
									*hpbarSpr->RenShader,
									hpbarSpr->MaxSize,
									params.GlobalPosition,
									params.LocalScale);

	return params;
}

GameObject* HeroLoadInfo::InstanceObject(LoadedObjects& levInfo, Vector2f position, vector<string>* additParams) {

	UnitObjectCtorParams& unParams = GetUnitParams();

	string* output = new string();
	if (ObjsCatalogDeserial::TryGetSerValueOfParam(*additParams, SerializationParDefNames::OBJECT_POSITION, output)) {
		unParams.GlobalPosition = ParseVec2f(*output);
	}
	else {
		unParams.GlobalPosition = position;
	}

	HeroObjectCtorParams& heParams = *new HeroObjectCtorParams(unParams);

	HeroObject* hero = new HeroObject(heParams);
	levInfo.LoadedUnits.push_front(hero);
	levInfo.LoadedHeroes.push_front(hero);
	//levInfo.LoadedGraphics.push_front(hero);

	delete output;
	delete &unParams;
	delete& heParams;

	return hero;
}

GameObject* WallLoadInfo::InstanceObject(LoadedObjects& levInfo, Vector2f position, vector<string>* additParams) {

	string* output = new string();
	if (additParams!=nullptr && 
		ObjsCatalogDeserial::TryGetSerValueOfParam(*additParams, SerializationParDefNames::OBJECT_POSITION, output)) {
		Position = ParseVec2f(*output);
	}
	else {
		Position = position;
	}

	FStreamExts::ClearPath(SpriteSource);
	ExtGlRes_Sprite* spr = dynamic_cast<ExtGlRes_Sprite*>(ExternalGlobalResources::GetRes(SpriteSource));
	return new WallObject(spr->Tex, Position, Size);
}