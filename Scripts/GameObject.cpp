
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
	delete& BodySprite;
	delete Transf;
}
GameObjectCtorParams::GameObjectCtorParams() 
	:CatalogID(ObjectsCatalog::EMPTY_CATALOG_ID),
	SubcatalogID(ObjectsCatalog::ABSENT_SUB_CATALOG_ID)
{}
GameObject::GameObject(const GameObjectCtorParams& params) 
	:DynamicPhysObject(),
	CatalogObject(params.CatalogID, params.SubcatalogID),
	WorldTransfObj(
		ctor_InitOwner(),
		params.GlobalPosition,
		params.GlobalScale),
	BodySprite(*new SpriteRenderer(
		params.BodySpriteSource->Tex,
		*this,
		Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution,
		Vector2f(0, 0),
		DEFAULT_SCALE_SNG,
		0,
		params.SprColor,
		params.BodySpriteSource->RenShader))
{}

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