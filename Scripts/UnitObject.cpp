
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

#include <VectExts.h>
using namespace KrostganEngine;

UnitObject::UnitObject(UnitObjectCtorParams& params)
	:Entity(params),
	Collider(*new CircleCollShape(params.GlobalPosition, params.GlobalScale* Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution * 0.5f)),
	Layer(PhysicsLayer::Units)
{
	cout << "Instance Unit: " << GetCatalogID() << ":" << (int)GetSubcatalogID() << endl;
}
UnitObject::~UnitObject() {
	delete &Collider;
}


PhysicsLayer UnitObject::GetLayer() const {
	return Layer;
}

void UnitObject::SetGlobalScale(Vector2f  scale) {
	Entity::SetGlobalScale(scale);
	Collider.Radius= GetGlobalScale_Sng() * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution * 0.5;
}
void UnitObject::SetGlobalPosition(Vector2f pos) {
	Entity::SetGlobalPosition(pos);
	Collider.Center = pos;
}

const vector<EntityOrderType>& UnitObject::GetAllowedOrdersCatalog() {
	return UnitObject::AllowedOrdersCatalog;
}

const ColliderShape& UnitObject::GetCollider_Action() const {
	return Collider;
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