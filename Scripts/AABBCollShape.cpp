
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

bool AABBCollShape::Intersect(AABBCollShape collision) const {
	return Intersect_AABBvsAABB(collision, *this);
}
bool AABBCollShape::Intersect(CircleCollShape collision) const {
	return Intersect_CircleVsAABB(collision, *this);
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
