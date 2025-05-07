
#include <Extensions.h>
#include <EngineCore.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Core;

bool ColliderShape::IsOverlap_CircleVsCircle(CircleCollShape coll1, CircleCollShape coll2) {
	float dist = SquareLength(coll1.Center - coll2.Center);
	float minDist = coll1.Radius + coll2.Radius;
	minDist *= minDist;
	float diff = minDist - dist;
	return diff >= eps;
}
bool ColliderShape::IsOverlap_CircleVsAABB(CircleCollShape coll1, AABBCollShape coll2) {
	bool isInHor = coll2.Min.x < coll1.Center.x && coll1.Center.x < coll2.Max.x;
	bool isInVer = coll2.Min.y < coll1.Center.y && coll1.Center.y < coll2.Max.y;
	if (isInHor&& isInVer)
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
bool ColliderShape::IsOverlap_AABBvsAABB(AABBCollShape coll1, AABBCollShape coll2) {
	return coll2.Min.x < coll1.Max.x &&
		coll1.Min.x < coll2.Max.x &&
		coll2.Min.y < coll1.Max.y &&
		coll1.Min.y < coll2.Max.y;
}

bool ColliderShape::IsPointInCollider(const CircleCollShape& coll, Vector2f point) {
	float dist = SquareLength(coll.Center - point);
	float minDist = (float)pow(coll.Radius,2);
	float diff = minDist - dist;
	return diff >= eps;
}
bool ColliderShape::IsPointInCollider(const AABBCollShape& coll, Vector2f point) {
	bool isXBigMin = point.x > coll.Min.x; //x bigger than min
	bool isXLesMax = point.x < coll.Max.x; //x less than max
	bool isYBigMin = point.y > coll.Min.y; //y bigger than min
	bool isYLesMax = point.y < coll.Max.y; //y less than max
	return isXBigMin && isXLesMax && isYBigMin && isYLesMax;
}

Vector2f ColliderShape::GetClosestPoint(const CircleCollShape& coll, Vector2f point) {
	Vector2f diff = point - coll.Center;
	diff = Normalize(diff);
	diff = diff*coll.Radius;
	diff += coll.Center;
	return diff;
}
Vector2f ColliderShape::GetClosestPoint(const AABBCollShape& coll, Vector2f point) {
	Vector2f clPoint;
	bool isXBigMin = point.x > coll.Min.x; //x bigger than min
	bool isXLesMax = point.x < coll.Max.x; //x less than max
	bool isYBigMin = point.y > coll.Min.y; //y bigger than min
	bool isYLesMax = point.y < coll.Max.y; //y less than max
	if (isXBigMin && isXLesMax &&
		isYBigMin && isYLesMax) {
		float distToEx_X, distToEx_Y;
		bool isLeft= point.x < (coll.Max.x + coll.Min.x) / 2;
		bool isBottom= point.y < (coll.Max.y + coll.Min.y) / 2;
		if (isLeft) {
			distToEx_X = point.x - coll.Min.x;
		}
		else {
			distToEx_X = coll.Max.x - point.x;
		}
		if (isBottom) {
			distToEx_Y = point.y - coll.Min.y;
		}
		else {
			distToEx_Y = coll.Max.y - point.y;
		}
		if (distToEx_X < distToEx_Y) {
			clPoint.y = point.y;
			if (isLeft)
				clPoint.x = coll.Min.x;
			else
				clPoint.x = coll.Max.x;
		}
		else {
			clPoint.x = point.x;
			if (isBottom)
				clPoint.y = coll.Min.y;
			else
				clPoint.y = coll.Max.y;
		}
	}
	else {
		if (isXBigMin) {
			if (isXLesMax) {
				clPoint.x = point.x;
			}
			else {
				clPoint.x = coll.Max.x;
			}
		}
		else {
			clPoint.x = coll.Min.x;
		}
		if (isYBigMin) {
			if (isYLesMax) {
				clPoint.y = point.y;
			}
			else {
				clPoint.y = coll.Max.y;
			}
		}
		else {
			clPoint.y = coll.Min.y;
		}
	}
	return clPoint;
}