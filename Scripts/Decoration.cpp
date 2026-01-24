
#include <Decoration.h>
#include <Engine.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;

DecorationObject::DecorationObject(DecorationCtorParams& params)
	:GameObject(params),
		COLLIDER(*((params.COLLIDER==nullptr)?new EmptyShape():params.COLLIDER)),
		HitEffectSprite(params.HitEffectSprite),
		IsTargetableForAutoAttack(params.IsTargetableForAutoAttack){

	params.Owner = this;

	params.InitDeathModule();
	params.InitHPModule();

	HPModule = params.GetHPModule();

	HitEffectSprite->SetGlobalPosition(GetGlobalPosition());
	HitEffectSprite->SetParent(this);

	COLLIDER.MoveCollider(GetGlobalPosition());
	RecreateCollider(1, GetGlobalScale_Sng());
}
DecorationObject::~DecorationObject() {
	delete& COLLIDER;
	delete HPModule;
}

void DecorationObject::RecreateCollider(float oldSize, float newSize) {

	COLLIDER.Resize(1 / oldSize);
	COLLIDER.Resize(newSize);
}

void DecorationObject::Update(CallbackRecArgs_LUpd args) {

}

void DecorationObject::SetGlobalPosition(Vector2f position) {

	Vector2f diff = position - GetGlobalPosition();
	COLLIDER.MoveCollider(diff);
	GameObject::SetGlobalPosition(position);
}
void DecorationObject::SetGlobalScale(Vector2f scale) {
	float oldScale = GetGlobalScale_Sng();
	GameObject::SetGlobalScale(scale);
	RecreateCollider(oldScale, GetGlobalScale_Sng());
}
void DecorationObject::SetLocalScale(Vector2f scale) {
	float oldScale = GetGlobalScale_Sng();
	GameObject::SetLocalScale(scale);
	RecreateCollider(oldScale, GetGlobalScale_Sng());
}
void DecorationObject::SetLocalPosition(Vector2f pos) {

	Vector2f oldPos = GetGlobalPosition();
	GameObject::SetLocalPosition(pos);
	COLLIDER.MoveCollider(GetGlobalPosition() - oldPos);
}

vector<IPhysicalObject*> DecorationObject::OverlapAll() const {
	return Engine::GetPhysicsEngine().OverlapDynamic_All(COLLIDER, SOLID_COLLISION_LAYER);
}
Vector2f DecorationObject::GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const {
	return objShape.GetCollisionResolvPoint_d(COLLIDER, movDir, isSlideColl);
}

PhysicsLayer DecorationObject::GetLayer() const {
	return PhysicsLayer::Decorations;
}
const ColliderShape& DecorationObject::GetCollider() const {
	return COLLIDER;
}

IHitPointModule& DecorationObject::GetHPModule() const {
	return *HPModule;
}
Vector2f DecorationObject::GetClosestPoint(Vector2f dmgDealerPos) const {
	return COLLIDER.GetClosestPoint(dmgDealerPos);
}
bool DecorationObject::IsTargetableForAA() const {
	return IsTargetableForAutoAttack;
}
void DecorationObject::SetTargetableForAA(bool isTargetable) {
	IsTargetableForAutoAttack = isTargetable;
}
