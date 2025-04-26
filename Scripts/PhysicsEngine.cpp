
#include <Physics.h>
#include <vector>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Physics;

PhysicsEngine::PhysicsEngine():EngineCallbackHandler<IPhysicalObject>(){}

vector<IPhysicalObject*> PhysicsEngine::OverlapAABB_All(Vector2f min, Vector2f max,PhysicsLayer layer) {
	AABBCollShape castShape = AABBCollShape(min, max);
	vector<IPhysicalObject*> objs = vector<IPhysicalObject*>();
	for (auto obj : Callbacks) {
		if (obj->IsCollide(castShape))
			objs.push_back(obj);
	}
	return objs;
}