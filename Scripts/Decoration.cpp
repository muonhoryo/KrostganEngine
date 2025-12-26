
#include <Decoration.h>
#include <Engine.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;

DecorationObject::DecorationObject(DecorationCtorParams& params)
	:GameObject(params),
		Collider(*((params.Collider==nullptr)?new EmptyShape():params.Collider)),
		//test
		//Collider(*new CircleCollShape(GetGlobalPosition(), Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution * 0.5f)),
		//test endl
		HitEffectSprite(params.HitEffectSprite),
		IsTargetableForAutoAttack(params.IsTargetableForAutoAttack){

	params.Owner = this;

	params.InitDeathModule();
	params.InitHPModule();

	HPModule = params.GetHPModule();

	HitEffectSprite->SetGlobalPosition(GetGlobalPosition());
	HitEffectSprite->SetParent(this);

	Collider.MoveCollider(GetGlobalPosition());
	RecreateCollider(1, GetGlobalScale_Sng());
}
DecorationObject::~DecorationObject() {
	delete& Collider;
	delete HPModule;
}

void DecorationObject::RecreateCollider(float oldSize, float newSize) {

	Collider.Resize(1 / oldSize);
	Collider.Resize(newSize);
}

void DecorationObject::Update(CallbackRecArgs_LUpd args) {

}

void DecorationObject::SetGlobalPosition(Vector2f position) {

	Vector2f diff = position - GetGlobalPosition();
	Collider.MoveCollider(diff);
	GameObject::SetGlobalPosition(position);
}
void DecorationObject::SetGlobalScale(Vector2f scale) {
	float oldScale = GetGlobalScale_Sng();
	GameObject::SetGlobalScale(scale);
	RecreateCollider(oldScale, GetGlobalScale_Sng());
}

vector<IPhysicalObject*> DecorationObject::OverlapAll() const {
	return Engine::GetPhysicsEngine().OverlapDynamic_All(Collider, SOLID_COLLISION_LAYER);
}
Vector2f DecorationObject::GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const {
	return objShape.GetCollisionResolvPoint_d(Collider, movDir, isSlideColl);
}

PhysicsLayer DecorationObject::GetLayer() const {
	return PhysicsLayer::Decorations;
}
const ColliderShape& DecorationObject::GetCollider() const {
	return Collider;
}

IHitPointModule& DecorationObject::GetHPModule() const {
	return *HPModule;
}
Vector2f DecorationObject::GetClosestPoint(Vector2f dmgDealerPos) const {
	return Collider.GetClosestPoint(dmgDealerPos);
}
bool DecorationObject::IsTargetableForAA() const {
	return IsTargetableForAutoAttack;
}
void DecorationObject::SetTargetableForAA(bool isTargetable) {
	IsTargetableForAutoAttack = isTargetable;
}
