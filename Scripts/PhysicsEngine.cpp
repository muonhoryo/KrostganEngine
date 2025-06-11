
#include <Physics.h>
#include <vector>
#include <SFML/System.hpp>
#include <Engine.h>
#include <Extensions.h>

using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine;

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
vector<IPhysicalObject*> PhysicsEngine::OverlapCircle_All(Vector2f center, float radius, PhysicsLayer layer) {
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
		if (layerCast!=0 && obj->GetCollider().IsPointInCollider(globalPos))
			return obj;
	}
	return nullptr;
}

bool PhysicsEngine::Intersect(const Ray& ray, const Segment& seg, Vector2f* interPnt) {

	Vector2f segDir = seg.Second - seg.First;
	Vector2f segN = Vector2f(segDir.y, -segDir.x);
	Vector2f rayN = Vector2f(ray.Direction.y, -ray.Direction.x);
	float segD = -Dot(seg.First, segN);
	float rayD = -Dot(ray.Origin, rayN);
	float t1 = segN.x * rayN.y - segN.y * rayN.y;
	float t2 = segN.x * rayD - rayN.x * segD;

	if (fabs(Dot(ray.Direction, segDir)) + eps >= 1)	//Check if ray and segment is parallel
		return false;

	float det = segN.x * rayN.y - segN.y * rayN.x;
	Vector2f p0 = Vector2f(
		(rayD * segN.y - segD * rayN.y) / det,
		(segD * rayN.x - rayD * segN.x) / det);
	if (min(seg.First.x, ray.Origin.x) <= p0.x && p0.x <= max(seg.First.x, ray.Origin.x) &&
		min(seg.First.y, ray.Origin.y) <= p0.y && p0.y <= max(seg.First.y, ray.Origin.y)) {
		*interPnt = p0;
		return true;
	}
	else {
		return false;
	}
}