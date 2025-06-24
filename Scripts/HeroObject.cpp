
#include <HeroObject.h>
#include <Engine.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <UnitObject.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

HeroObject::HeroObject(HeroObjectCtorParams& params) : UnitObject(params){}
HeroObject::~HeroObject(){}

const Texture& HeroObject::GetSelectionTexture() {
	return *Engine::GetGlobalResources().HeroesSelectionAreaSprite;
}
float HeroObject::GetSelectSpriteMaxSize() {
	return Engine::GetGlobalConsts().HeroesSelectArea_OneSizeSpriteResol;
}