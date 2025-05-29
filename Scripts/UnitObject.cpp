
#include <SFML/System.hpp>
#include <CoreGameObjects.h>
#include <UnitObject.h>
#include <SFML/Graphics.hpp>
#include <Entity.h>
#include <Engine.h>
#include <vector>
#include <CoreEntitiesControl.h>

#include <PrimitiveVisualShapes.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;
using namespace KrostganEngine::EntitiesControl;

UnitObject::UnitObject(UnitObjectCtorParams& params)
	:Entity(params){
	Collider = new CircleCollShape(params.Position, params.Size * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution * 0.5f);
	Layer = PhysicsLayer::Units;
}
UnitObject::~UnitObject() {
	delete Collider;
}


PhysicsLayer UnitObject::GetLayer() const {
	return Layer;
}

void UnitObject::SetScale(float scale) {
	Entity::SetScale(scale);
	Collider->Radius= scale * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution/2;
}
void UnitObject::SetPosition(Vector2f pos) {
	Entity::SetPosition(pos);
	Collider->Center = pos;
}

const vector<EntityOrderType>& UnitObject::GetAllowedOrdersCatalog() {
	return UnitObject::AllowedOrdersCatalog;
}

const ColliderShape& UnitObject::GetCollider() const {
	return *Collider;
}
bool UnitObject::IsCollideShape(const ColliderShape& shape) const {
	return shape.Intersect(*Collider);
}

Vector2f UnitObject::GetClosestPoint(Vector2f source) const {
	return Collider->GetClosestPoint(source);
}

const Texture& UnitObject::GetSelectionTexture() {
	return Engine::GetGlobalResources().UnitsSelectionAreaSprite;
}
float UnitObject::GetSelectSpriteMaxSize() {
	return Engine::GetGlobalConsts().UnitsSelectArea_OneSizeSpriteResol;
}

const vector<EntityOrderType> UnitObject::AllowedOrdersCatalog = vector<EntityOrderType>
{
EntityOrderType::MovingToPoint,
EntityOrderType::AttackTarget,
EntityOrderType::HoldPosition
};