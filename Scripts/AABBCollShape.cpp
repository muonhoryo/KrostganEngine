
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

bool AABBCollShape::IsOverlap(AABBCollShape collision) const {
	return IsOverlap_AABBvsAABB(collision, *this);
}
bool AABBCollShape::IsOverlap(CircleCollShape collision) const {
	return IsOverlap_CircleVsAABB(collision, *this);
}
bool AABBCollShape::IsPointInCollider(Vector2f point) const {
	return ColliderShape::IsPointInCollider(*this, point);
}
Vector2f AABBCollShape::GetClosestPoint(Vector2f point) const {
	return ColliderShape::GetClosestPoint(*this, point);
}
