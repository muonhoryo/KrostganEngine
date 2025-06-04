
#include "ColliderShapes.h"

using namespace KrostganEngine::Physics;

AABBCollShape::AABBCollShape(Vector2f Min,Vector2f Max)
{
	if (Min.x > Max.x ||
		Min.y > Max.y)
		throw std::exception("Incorrect params of AABB shape");

	this->Min = Min;
	this->Max = Max;
}

bool AABBCollShape::Intersect(const AABBCollShape& collision) const {
	return Intersect_AABBvsAABB(collision, *this);
}
bool AABBCollShape::Intersect(const CircleCollShape& collision) const {
	return Intersect_CircleVsAABB(collision, *this);
}
bool AABBCollShape::Intersect(const ColliderShape* coll[], size_t count)const {
	int index = 0;
	while (index < count) {
		if (coll[index]->Intersect(*this))
			return true;
	}
	return false;
}

bool AABBCollShape::GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, Vector2f* resolvPnt) const {
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	*resolvPnt = Vector2f(1, 0);
	return true;
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
}
bool AABBCollShape::GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, Vector2f* resolvPnt) const {
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	*resolvPnt = Vector2f(1, 0);
	return true;
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
}

bool AABBCollShape::IsPointInCollider(Vector2f point) const {
	bool isXBigMin = point.x > Min.x; //x bigger than min
	bool isXLesMax = point.x < Max.x; //x less than max
	bool isYBigMin = point.y > Min.y; //y bigger than min
	bool isYLesMax = point.y < Max.y; //y less than max
	return isXBigMin && isXLesMax && isYBigMin && isYLesMax;
}
Vector2f AABBCollShape::GetClosestPoint(Vector2f point) const {
	Vector2f clPoint;
	bool isXBigMin = point.x > Min.x; //x bigger than min
	bool isXLesMax = point.x < Max.x; //x less than max
	bool isYBigMin = point.y > Min.y; //y bigger than min
	bool isYLesMax = point.y < Max.y; //y less than max
	if (isXBigMin && isXLesMax &&
		isYBigMin && isYLesMax) {
		float distToEx_X, distToEx_Y;
		bool isLeft = point.x < (Max.x + Min.x) / 2;
		bool isBottom = point.y < (Max.y + Min.y) / 2;
		if (isLeft) {
			distToEx_X = point.x - Min.x;
		}
		else {
			distToEx_X = Max.x - point.x;
		}
		if (isBottom) {
			distToEx_Y = point.y - Min.y;
		}
		else {
			distToEx_Y = Max.y - point.y;
		}
		if (distToEx_X < distToEx_Y) {
			clPoint.y = point.y;
			if (isLeft)
				clPoint.x = Min.x;
			else
				clPoint.x = Max.x;
		}
		else {
			clPoint.x = point.x;
			if (isBottom)
				clPoint.y = Min.y;
			else
				clPoint.y = Max.y;
		}
	}
	else {
		if (isXBigMin) {
			if (isXLesMax) {
				clPoint.x = point.x;
			}
			else {
				clPoint.x = Max.x;
			}
		}
		else {
			clPoint.x = Min.x;
		}
		if (isYBigMin) {
			if (isYLesMax) {
				clPoint.y = point.y;
			}
			else {
				clPoint.y = Max.y;
			}
		}
		else {
			clPoint.y = Min.y;
		}
	}
	return clPoint;
}
bool AABBCollShape::IntersectRay(const Ray& ray, Vector2f* interPnt) const {
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	*interPnt = Vector2f(0, 0);
	return true;
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
}
