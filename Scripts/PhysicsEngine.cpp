
#include <Physics.h>
#include <vector>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Physics;

PhysicsEngine::PhysicsEngine():EngineCallbackHandler<IPhysicalObject>(){}

vector<IPhysicalObject*> PhysicsEngine::OverlapAABB_All(Vector2f min, Vector2f max,PhysicsLayer layer) {
	AABBCollShape castShape = AABBCollShape(min, max);
	vector<IPhysicalObject*> objs = vector<IPhysicalObject*>();
	size_t layerCast;
	for (auto obj : Callbacks) {
		layerCast = (size_t)obj->GetLayer() & (size_t)layer;
		if (layerCast!=0 && obj->IsCollide(castShape))
			objs.push_back(obj);
	}
	return objs;
}

IPhysicalObject* PhysicsEngine::PointCast(Vector2f globalPos, PhysicsLayer layer) {
	size_t layerCast;
	for (auto obj : Callbacks) {
		layerCast = (size_t)obj->GetLayer() & (size_t)layer;
		if (layerCast!=0 && obj->IsInCollider(globalPos))
			return obj;
	}
	return nullptr;
}