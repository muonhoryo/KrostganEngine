
#include <Physics.h>
#include <vector>
#include <SFML/System.hpp>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine::Physics;

PhysicsEngine::PhysicsEngine():EngineCallbackHandler<IPhysicalObject>(){}

vector<IPhysicalObject*> PhysicsEngine::OverlapAABB_All(Vector2f min, Vector2f max,PhysicsLayer layer) {
	AABBCollShape* shape = new AABBCollShape(min, max);
	vector<IPhysicalObject*> objs = Overlap_All<AABBCollShape>(*shape, layer);
	delete shape;
	return objs;
}

/// <summary>
/// Return empty array if there is not any physics in over circle or radius is too small for cast
/// </summary>
/// <param name="center"></param>
/// <param name="radius"></param>
/// <param name="layer"></param>
/// <returns></returns>
vector<IPhysicalObject*> PhysicsEngine::OverlapCircl_All(Vector2f center, float radius, PhysicsLayer layer) {
	if (radius <= eps)
		return vector<IPhysicalObject*>();

	CircleCollShape* castShape =new CircleCollShape(center, radius);
	auto objs = Overlap_All<CircleCollShape>(*castShape, layer);
	delete castShape;
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