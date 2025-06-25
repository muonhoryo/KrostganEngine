
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
		params.Position = ParseVec2f(*output);
	}
	else {
		params.Position = position;
	}

	UnitObject* unit = new UnitObject(params);
	levInfo.LoadedUnits.push_front(unit);
	levInfo.LoadedGraphics.push_front(unit);

	delete output;
	delete &params;

	return unit;
}

UnitObjectCtorParams& UnitLoadInfo::GetUnitParams() {

	Texture* texBuffer = new Texture();
	texBuffer->loadFromFile(TexturePath);
	UnitObjectCtorParams& params = *new UnitObjectCtorParams();

	params.BattleStats		=		new EntityBattleStats(*BattleStats);
	params.EntityFraction	=		EntityFraction;
	params.RenTexture		=		texBuffer;
	params.RenOffset		=		SpriteOffset;
	params.Position			=		Position;
	params.Size				=		Size;
	return params;
}

GameObject* HeroLoadInfo::InstanceObject(LoadedObjects& levInfo, Vector2f position, vector<string>* additParams) {

	UnitObjectCtorParams& unParams = GetUnitParams();

	string* output = new string();
	if (ObjsCatalogDeserial::TryGetSerValueOfParam(*additParams, SerializationParDefNames::OBJECT_POSITION, output)) {
		unParams.Position = ParseVec2f(*output);
	}
	else {
		unParams.Position = position;
	}

	HeroObjectCtorParams& heParams = *new HeroObjectCtorParams(unParams);

	HeroObject* hero = new HeroObject(heParams);
	levInfo.LoadedUnits.push_front(hero);
	levInfo.LoadedHeroes.push_front(hero);
	levInfo.LoadedGraphics.push_front(hero);

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


	Texture* texBuffer = new Texture();
	texBuffer->loadFromFile(TexturePath);
	return new WallObject(*texBuffer, SpriteOffset, Position, Size);
}