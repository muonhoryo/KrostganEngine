
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
	:Entity(params),
	Collider(*new CircleCollShape(params.Position, params.Size* Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution * 0.5f)),
	Layer(PhysicsLayer::Units){
}
UnitObject::~UnitObject() {
	delete &Collider;
}


PhysicsLayer UnitObject::GetLayer() const {
	return Layer;
}

void UnitObject::SetScale(float scale) {
	Entity::SetScale(scale);
	Collider.Radius= scale * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution/2;
}
void UnitObject::SetPosition(Vector2f pos) {
	Entity::SetPosition(pos);
	Collider.Center = pos;
}

const vector<EntityOrderType>& UnitObject::GetAllowedOrdersCatalog() {
	return UnitObject::AllowedOrdersCatalog;
}

const ColliderShape& UnitObject::GetCollider_Action() const {
	return Collider;
}

const Texture& UnitObject::GetSelectionTexture() {
	return Engine::GetGlobalResources().UnitsSelectionAreaSprite;
}
float UnitObject::GetSelectSpriteMaxSize() {
	return Engine::GetGlobalConsts().UnitsSelectArea_OneSizeSpriteResol;
}

vector<IPhysicalObject*> UnitObject::OverlapAll_Action() const {
	return Engine::GetPhysicsEngine().OverlapCircle_All(Collider.Center, Collider.Radius, SOLID_COLLISION_LAYER);
}
Vector2f UnitObject::GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const {

	return objShape.GetCollisionResolvPoint(Collider, movDir,isSlideColl);
}

Vector2f UnitObject::GetClosestPoint(Vector2f dmgDealerPos) const {
	return Collider.GetClosestPoint(dmgDealerPos);
}

const vector<EntityOrderType> UnitObject::AllowedOrdersCatalog = vector<EntityOrderType>
{
EntityOrderType::MovingToPoint,
EntityOrderType::FollowTarget,
EntityOrderType::AttackTarget,
EntityOrderType::AttackArea,
EntityOrderType::HoldPosition,
EntityOrderType::Cancel,
EntityOrderType::Idle
};