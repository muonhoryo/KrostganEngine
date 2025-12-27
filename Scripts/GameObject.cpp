
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <Extensions.h>
#include <Engine.h>
#include <TransformableObj.h>
#include <ObjectsCatalog.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

GameObject::~GameObject() {
}
GameObjectCtorParams::GameObjectCtorParams() 
	:CatalogID(ObjectsCatalog::EMPTY_CATALOG_ID),
	SubcatalogID(ObjectsCatalog::ABSENT_SUB_CATALOG_ID)
{}
GameObject::GameObject(const GameObjectCtorParams& params) 
	:DynamicPhysObject(),
	CatalogObject(params.CatalogID, params.SubcatalogID),
	WorldTransfObj(*new Transformable()),
	BodySprite(*new SpriteRenderer(
		params.BodySpriteSource->Tex,
		*this,
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution,
		params.BodySpriteSource->RenShader)),
	SolidCollision(params.SolidCollision)
{
	SetGlobalPosition(params.GlobalPosition);
	SetGlobalScale_Sng(params.GlobalScale);
	SetGlobalRotation(params.GlobalRotation);
	
	BodySprite.SetColor(params.SprColor);
}

void GameObject::SetGlobalPosition(Vector2f position) {

	WorldTransfObj::SetGlobalPosition(position);
	HasMoved = true;
}
void GameObject::SetLocalPosition(Vector2f position) {

	WorldTransfObj::SetLocalPosition(position);
	HasMoved = true;
}
void GameObject::SetGlobalScale(Vector2f scale) {

	float scl = GetScale_Inter(scale);
	WorldTransfObj::SetGlobalScale(Vector2f(scl, scl));
}
void GameObject::SetLocalScale(Vector2f scale) {
	float scl = GetScale_Inter(scale);
	WorldTransfObj::SetLocalScale(Vector2f(scl, scl));
}
float GameObject::GetScale_Inter(const Vector2f& scale) const {
	return min(scale.x, scale.y);
}

Color	GameObject::GetColor() const {
	return BodySprite.GetColor();
}
void	GameObject::SetColor(Color color) {
	BodySprite.SetColor(color);
}

bool GameObject::IsSolidCollision() const {
	return SolidCollision;
}

void GameObject::Set_IsSolidCollision(bool isSolidColl) {
	SolidCollision = isSolidColl;
}