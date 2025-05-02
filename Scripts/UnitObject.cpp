
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

UnitObject::UnitObject(EntityBattleStats& BattleStats,const Texture& RenTexture, Vector2f RenOffset, Vector2f Position,float Size)
	:Entity(BattleStats,RenTexture, RenOffset, Position,Size){
	Collider = new CircleCollShape(Position, Size * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution * 0.5f);
	Layer = PhysicsLayer::Units;

	testCircle = new CircleVisPrimitive(Position, Collider->Radius, Color::Green, 30);
}
UnitObject::~UnitObject() {
	delete testCircle;
	delete Collider;
}


PhysicsLayer UnitObject::GetLayer() {
	return Layer;
}

void UnitObject::SetScale(float scale) {
	Entity::SetScale(scale);
	Collider->Radius= scale * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution/2;

	testCircle->SetRadius(Collider->Radius);
}
void UnitObject::SetPosition(Vector2f pos) {
	Entity::SetPosition(pos);
	Collider->Center = pos;

	testCircle->SetCenter(pos);
}

const vector<EntityOrderType>& UnitObject::GetAllowedOrdersCatalog() {
	return UnitObject::AllowedOrdersCatalog;
}

const ColliderShape& UnitObject::GetCollider() const {
	return *Collider;
}
bool UnitObject::IsCollideShape(const ColliderShape& shape) const {
	return shape.IsOverlap(*Collider);
}
const Texture& UnitObject::GetSelectionTexture() {
	return Engine::GetGlobalResources().UnitsSelectionAreaSprite;
}
float UnitObject::GetSelectSpriteMaxSize() {
	return Engine::GetGlobalConsts().UnitsSelectArea_OneSizeSpriteResol;
}

const vector<EntityOrderType> UnitObject::AllowedOrdersCatalog = vector<EntityOrderType> {EntityOrderType::MovingToPoint};