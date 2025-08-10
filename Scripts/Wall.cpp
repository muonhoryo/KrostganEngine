
#include <Wall.h>
#include <Engine.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;

WallObject::WallObject(const Texture& RenTexture, Vector2f Position, float Size) 
	:GameObject(RenTexture,Position,Size){

	float innerRad = Size * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution*0.5f;
	Collider = new AABBCollShape(Vector2f(Position.x - innerRad, Position.y - innerRad), Vector2f(Position.x + innerRad, Position.y + innerRad));
}
WallObject::~WallObject() {
	delete Collider;
}

PhysicsLayer WallObject::GetLayer() const {
	return PhysicsLayer::Decorations;
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
