
#include <SFML/System.hpp>
#include <EngineCore.h> 
#include <Extensions.h>

using namespace sf;
using namespace KrostganEngine::Physics;

CircleCollShape::CircleCollShape(Vector2f Center, float Radius)
{
	if (Radius<=0)
		throw exception("Radius of circle cannot be less than zero");

	this->Center= Center;
	this->Radius= Radius;
}

bool CircleCollShape::Intersect(AABBCollShape collision) const {
	return Intersect_CircleVsAABB(*this, collision);
}
bool CircleCollShape::Intersect(CircleCollShape collision)const {
	return Intersect_CircleVsCircle(collision, *this);
}
bool CircleCollShape::IsPointInCollider(Vector2f point) const {
	float dist = SquareLength(Center - point);
	float minDist = (float)pow(Radius, 2);
	float diff = minDist - dist;
	return diff >= eps;
}
Vector2f CircleCollShape::GetClosestPoint(Vector2f point)const {
	Vector2f diff = point - Center;
	diff = Normalize(diff);
	diff = diff * Radius;
	diff += Center;
	return diff;
}