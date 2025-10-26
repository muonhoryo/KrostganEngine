
#include <Wall.h>
#include <Engine.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;

void WallObject::RecreateCollider() {
	float innerRad = GetGlobalScale_Sng()* Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution * 0.5f;
	Vector2f pos = GetGlobalPosition();
	Collider = new AABBCollShape(Vector2f(pos.x - innerRad, pos.y - innerRad), Vector2f(pos.x + innerRad, pos.y + innerRad));
}
WallObject::WallObject(const WallCtorParams& params)
	:GameObject(params){

	RecreateCollider();
}
WallObject::~WallObject() {
	delete Collider;
}

PhysicsLayer WallObject::GetLayer() const {
	return PhysicsLayer::Decorations;
}

void WallObject::SetGlobalPosition(Vector2f position) {
	GameObject::SetGlobalPosition(position);
	RecreateCollider();
}
void WallObject::SetGlobalScale(Vector2f scale) {
	GameObject::SetGlobalScale(scale);
	RecreateCollider();
}

const ColliderShape& WallObject::GetCollider() const {
	return *Collider;
}
vector<IPhysicalObject*> WallObject::OverlapAll() const {
	return Engine::GetPhysicsEngine().OverlapAABB_All(Collider->Min, Collider->Max, SOLID_COLLISION_LAYER);
}
Vector2f WallObject::GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const {

	return objShape.GetCollisionResolvPoint(*Collider, movDir,isSlideColl);
}
