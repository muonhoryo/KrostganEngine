
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

vector<IPhysicalObject*> PhysicsEngine::RayCast_All(Vector2f origin, Vector2f direction, float distance, PhysicsLayer layer) {
	Vector2f second = origin + Vector2f(direction.x * distance, direction.y * distance);
	return RayCast_All(*new Segment(origin,second), layer);
}
vector<IPhysicalObject*> PhysicsEngine::RayCast_All(const Segment& segm, PhysicsLayer layer) {

	vector<IPhysicalObject*> result;
	float diffX = segm.First.x - segm.Second.x;
	float diffY = segm.First.y - segm.Second.y;
	if (diffX<eps || diffX>-eps ||
		diffY<eps || diffY>-eps) {


		for (auto tar : Callbacks) {

			if (tar == nullptr)
				continue;
			
			if (((int)tar->GetLayer() & (int)layer) != 0)
				result.push_back(tar);
		}
	}
	else {

		vector<IPhysicalObject*> potentTargets = OverlapAABB_All(segm.First, segm.Second, layer);
		for (IPhysicalObject* tar : potentTargets) {
			if (((int)tar->GetLayer() & (int)layer) != 0)
				result.push_back(tar);
		}
	}
	return result;
}

IPhysicalObject* PhysicsEngine::PointCast(Vector2f globalPos, PhysicsLayer layer) {
	
	size_t layerCast;

	for (auto obj : Callbacks) {

		if (obj == nullptr)
			continue;

		layerCast = (size_t)obj->GetLayer() & (size_t)layer;
		if (layerCast!=0 && obj->GetCollider().IsPointInCollider(globalPos))
			return obj;
	}
	return nullptr;
}

bool PhysicsEngine::RayHit(Segment segm, PhysicsLayer layer) {

	float diffX = segm.First.x - segm.Second.x;
	float diffY = segm.First.y - segm.Second.y;
	int maskCastRes;
	if (diffX<eps || diffX>-eps ||
		diffY<eps || diffY>-eps) {

		for (auto tar : Callbacks) {

			if (tar == nullptr)
				continue;

			maskCastRes = ((int)tar->GetLayer()) & ((int)layer);
			if (maskCastRes != 0 && tar->GetCollider().IntersectSegment(segm)) {

				return true;
			}
		}
	}
	else {

		vector<IPhysicalObject*> potentTargets = OverlapAABB_All(segm.First, segm.Second, layer);
		for (IPhysicalObject* tar : potentTargets) {
			maskCastRes = ((int)tar->GetLayer()) & ((int)layer);
			if (maskCastRes != 0 && tar->GetCollider().IntersectSegment(segm)) {

				return true;
			}
		}
	}
	return false;

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
bool PhysicsEngine::Intersect(const Segment& first, const Segment& second, Vector2f* interPnt) {


	if (max(first.First.x, first.Second.x) < min(second.First.x, second.Second.x) ||
		min(first.First.x, first.Second.x) > max(second.First.x, second.Second.x) ||
		max(first.First.y, first.Second.y) < min(second.First.y, second.Second.y) ||
		min(first.First.y, first.Second.y) > max(second.First.y, second.Second.y)) {
		return false;
	}

	float area1 = ((first.Second.x - first.First.x) * (second.First.y - first.First.y) -
		(first.Second.y - first.First.y) * (second.First.x - first.First.x)) *
		((first.Second.x - first.First.x) * (second.Second.y - first.First.y) -
			(first.Second.y - first.First.y) * (second.Second.x - first.First.x));
	float area2 = ((second.Second.x - second.First.x) * (first.First.y - second.First.y) -
		(second.Second.y - second.First.y) * (first.First.x - second.First.x)) *
		((second.Second.x - second.First.x) * (first.Second.y - second.First.y) -
			(second.Second.y - second.First.y) * (first.Second.x - second.First.x));

	return area1 <= 0 && area2 <= 0;
	//Vector2f dir1 = first.Second- first.First;
	//Vector2f dir2 = second.Second - second.First;
	//Vector2f n1 = Vector2f(dir1.y, -dir1.x);
	//Vector2f n2 = Vector2f(dir2.y, -dir2.x);
	//float det = n1.x * n2.y - n1.y * n2.x;
	//if (det<eps && det>-eps) {
	//	return false;
	//}
	//float d1 = -Dot(first.First, n1);
	//float d2 = -Dot(second.First, n2);

	//*interPnt = Vector2f((d2 * n1.y - d1 * n2.y) / det, (d1 * n2.x - d2 * n1.x) / det);

	////x
	//if (first.First.x > first.Second.x) {
	//	if (interPnt->x > first.First.x)
	//		return false;
	//	else if (interPnt->x < first.Second.x)
	//		return false;
	//}
	//else {
	//	if (interPnt->x > first.Second.x)
	//		return false;
	//	else if (interPnt->x < first.First.x)
	//		return false;
	//}

	//if (second.First.x > second.Second.x) {
	//	if (interPnt->x > second.First.x)
	//		return false;
	//	else if (interPnt->x < second.Second.x)
	//		return false;
	//}
	//else {
	//	if (interPnt->x > second.Second.x)
	//		return false;
	//	else if (interPnt->x < second.First.x)
	//		return false;
	//}
	////y
	//if (first.First.y > first.Second.y) {
	//	if (interPnt->y > first.First.y)
	//		return false;
	//	else if (interPnt->y < first.Second.y)
	//		return false;
	//}
	//else {
	//	if (interPnt->y > first.Second.y)
	//		return false;
	//	else if (interPnt->y < first.First.y)
	//		return false;
	//}

	//if (second.First.x > second.Second.x) {
	//	if (interPnt->x > second.First.x)
	//		return false;
	//	else if (interPnt->x < second.Second.x)
	//		return false;
	//}
	//else {
	//	if (interPnt->x > second.Second.x)
	//		return false;
	//	else if (interPnt->x < second.First.x)
	//		return false;
	//}
	//return true;
}
float PhysicsEngine::DistanceToPoint(const Segment& segm, Vector2f pnt) {

	Vector2f delta = segm.Second - segm.First;
	Vector2f diff = pnt - delta;
	float t = Dot(segm.First, diff);
	if (t > 0)
	{
		float dt = Length(delta);
		if (t < dt)
			t /= dt;
		else
			t = 1;
	}
	else
		t = 0;
	return Length(segm.First + t * delta - pnt);
}
PhysicsEngine::PointClassify PhysicsEngine::Classify(const Segment& segm, Vector2f pnt) {
	
	Vector2f a2b = segm.Second - segm.First;
	Vector2f a2p = pnt - segm.First;
	float area = a2b.x * a2p.y - a2p.x * a2b.y;

	if (area > eps)
		return PointClassify::Left;

	if (area < -eps)
		return PointClassify::Right;

	if (Length(a2p) < eps)
		return PointClassify::Start;

	if (Length(pnt - segm.Second) < eps)
		return PointClassify::End;

	if (((a2b.x * a2p.x) < 0) || ((a2b.y * a2p.y) < 0))
		return PointClassify::Behind;

	if (Length(a2b) < Length(a2p))
		return PointClassify::Beyond;

	return PointClassify::Between;

}