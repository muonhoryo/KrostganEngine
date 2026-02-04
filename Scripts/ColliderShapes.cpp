
#include <_Extensions.h>
#include <_EngineCore.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Core;

bool ColliderShape::Intersect_CircleVsCircle(const CircleCollShape& coll1, const CircleCollShape& coll2) {

	if (coll1.Radius < eps || coll2.Radius < eps)
		return false;

	float dist = SquareLength(coll1.Center - coll2.Center);
	float minDist = coll1.Radius + coll2.Radius;
	minDist *= minDist;
	float diff = minDist - dist;
	return diff >= eps;
}
bool ColliderShape::Intersect_CircleVsAABB(const CircleCollShape& coll1,const AABBCollShape& coll2) {
	
	if (coll1.Radius < eps)
		return false;

	bool isInHor = coll2.Min.x < coll1.Center.x && coll1.Center.x < coll2.Max.x;
	bool isInVer = coll2.Min.y < coll1.Center.y && coll1.Center.y < coll2.Max.y;
	if (isInHor&& isInVer)	//circle is inside aabb
		return true;
	else {
		float dist;
		if (isInHor) {
			if (coll1.Center.y > coll2.Max.y)
				dist = coll1.Center.y - coll2.Max.y;
			else
				dist = coll2.Min.y - coll1.Center.y;
		}
		else if (isInVer) {
			if (coll1.Center.x > coll2.Max.x)
				dist = coll1.Center.x - coll2.Max.x;
			else
				dist = coll2.Min.x - coll1.Center.x;
		}
		else {
			Vector2f nearP;
			if (coll1.Center.x < coll2.Min.x)
				nearP.x = coll2.Min.x;
			else
				nearP.x = coll2.Max.x;
			if (coll1.Center.y < coll2.Min.y)
				nearP.y = coll2.Min.y;
			else
				nearP.y = coll2.Max.y;
			dist = Length(nearP - coll1.Center);
		}
		return (coll1.Radius - dist)>=eps;
	}
}
bool ColliderShape::Intersect_AABBvsAABB(const AABBCollShape& coll1,const AABBCollShape& coll2) {
	return coll2.Min.x < coll1.Max.x &&
		coll1.Min.x < coll2.Max.x &&
		coll2.Min.y < coll1.Max.y &&
		coll1.Min.y < coll2.Max.y;
}
bool ColliderShape::Intersect_PolygonVsCircle(const PolygonCollShape& coll1, const CircleCollShape& coll2) {

	if (coll2.Radius < eps)
		return false;

	auto& circle = coll1.GetOutterBoundCircle();
	if (!Intersect_CircleVsCircle(circle, coll2))
		return false;
	
	auto& points = coll1.GetPoints();
	Vector2f a = points[points.size()-1];	//get last point
	Vector2f b;
	bool isInsideColl = true;
	for (auto it = points.cbegin();it != points.cend();++it) {
		b = *it;
		if (DistanceToLine(a, b, coll2.Center) <= coll2.Radius)
			return true;

		//Check is circle inside polygon
		//If center of circle is not by right-side of every edge of polygon circle cannot be inside of polygon
		if (isInsideColl && GetDimRelToLine_Left(a, b, coll2.Center)) {
			
			isInsideColl = false;
		}

		a = b;
	}
	return isInsideColl;
}
bool ColliderShape::Intersect_PolygonVsAABB(const PolygonCollShape& col11, const AABBCollShape& coll2) {

	//TODO
	//Do something with that

	return false;
}
bool ColliderShape::Intersect_PolygonVsPolygon(const PolygonCollShape& coll1, const PolygonCollShape& coll2) {

	//TODO
	//Currently are not wanted

	return false;
}

Vector2f ColliderShape::GetCollisionResolvPoint_d(const ColliderShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {

	const AABBCollShape* aabbSh = dynamic_cast<const AABBCollShape*>(&subjShape);
	if (aabbSh != nullptr)
		return GetCollisionResolvPoint(*aabbSh, subjMovDir, isSlideColl);

	const CircleCollShape* circleSh = dynamic_cast<const CircleCollShape*>(&subjShape);
	if (circleSh != nullptr)
		return GetCollisionResolvPoint(*circleSh, subjMovDir, isSlideColl);

	return DEFAULT_POSITION;
}