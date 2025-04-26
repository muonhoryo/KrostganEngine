
#include <SFML/System.hpp>
#include <EngineCore.h> 

using namespace sf;
using namespace KrostganEngine::Physics;

CircleCollShape::CircleCollShape(Vector2f Center, float Radius)
{
	if (Radius<=0)
		throw exception("Radius of circle cannot be less than zero");

	this->Center= Center;
	this->Radius= Radius;
}

bool CircleCollShape::IsOverlap(AABBCollShape collision) const {
	return IsOverlap_CircleVsAABB(*this, collision);
}
bool CircleCollShape::IsOverlap(CircleCollShape collision)const {
	return IsOverlap_CircleVsCircle(collision, *this);
}
