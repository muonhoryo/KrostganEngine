
#include <SFML/System.hpp>
#include <_EngineCore.h> 
#include <_Extensions.h>

using namespace sf;
using namespace KrostganEngine::Physics;

CircleCollShape::CircleCollShape(Vector2f Center, float Radius)
{
	this->Center= Center;
	this->Radius= Radius;
}

ColliderShape& CircleCollShape::Clone() const {

	return *new CircleCollShape(Center, Radius);
}

bool CircleCollShape::Intersect(const AABBCollShape& collision) const {
	return Intersect_CircleVsAABB(*this, collision);
}
bool CircleCollShape::Intersect(const CircleCollShape& collision)const {
	return Intersect_CircleVsCircle(collision, *this);
}
bool CircleCollShape::Intersect(const PolygonCollShape& objShape) const {
	return Intersect_PolygonVsCircle(objShape, *this);
}
bool CircleCollShape::Intersect(const ColliderShape* coll[], size_t count)const {
	int index = 0;
	while (index < count) {
		if(coll[index]->Intersect(*this))
			return true;
	}
	return false;
}

Vector2f CircleCollShape::GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {

	if (isSlideColl) {

		float diff;
		Vector2f dir = subjShape.Center - Center;
		diff = Radius + subjShape.Radius - Length(dir);

		if (diff < 0)
			return subjShape.Center;

		dir = Normalize(dir);
		return  subjShape.Center + Vector2f(dir.x * diff, dir.y * diff);
	}
	else {


		if (Radius < eps || subjShape.Radius < eps)
			return subjShape.Center;

		Vector2f mid = subjShape.Center - Center;
		float relat = Radius / (subjShape.Radius + Radius);
		mid = Vector2f(mid.x * relat, mid.y * relat);
		mid = Center + mid;
		Ray ray = Ray(mid, subjMovDir);
		Vector2f st;
		if (!subjShape.IntersectRay(ray, &st))
			return subjShape.Center;
		ray.Direction = -ray.Direction;
		Vector2f en;
		if (!IntersectRay(ray, &en))
			return subjShape.Center;
		en = en - st;
		return subjShape.Center + en;

	}

}
Vector2f CircleCollShape::GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {

	//TODO

	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	throw exception("Unimplemented method");
	return Vector2f(1, 0);
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
}
Vector2f CircleCollShape::GetCollisionResolvPoint(const PolygonCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {
	//TODO

	throw exception("Unimplemented method");
}

bool CircleCollShape::IsPointInCollider(Vector2f point) const {
	float dist = SquareLength(Center - point);
	float minDist = (float)pow(Radius, 2);
	float diff = minDist - dist;
	return diff >= eps;
}
Vector2f CircleCollShape::GetClosestPoint(Vector2f point)const {

	if (Radius < eps)
		return point;

	Vector2f diff = point - Center;
	diff = Normalize(diff);
	diff = diff * Radius;
	diff += Center;
	return diff;
}
bool CircleCollShape::IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest) const {
	Vector2f l = Center - ray.Origin;
	float l2oc = Dot(l, l);
	float tca = Dot(l, ray.Direction);
	float t2hc = Radius * Radius - l2oc + tca * tca;
	
	if (t2hc < eps)
		return false;

	float t1, t2;
	t2hc = sqrtf(t2hc);
	if (t2hc - tca > eps)
	{
		t1 = tca + t2hc;
		t2 = tca - t2hc;
	}
	else {
		t1 = tca - t2hc;
		t2 = tca + t2hc;
	}
	if (t1 < eps)
		t1 = t2;
	else if (t2 < eps)
		t2 = t1;
	else
	{
		if (selFarthest)
			t1 = max(t1, t2);
		else
			t1 = min(t1, t2);
	}

	*interPnt = Vector2f(
		ray.Origin.x + ray.Direction.x * t1,
		ray.Origin.y + ray.Direction.y * t1);
	return true;
}
bool CircleCollShape::IntersectSegment(const Segment& segm) const {

	float dist = PhysicsEngine::DistanceToPoint(segm, Center);
	return dist - Radius < eps;
}

const CircleCollShape& CircleCollShape::GetOutterBoundCircle()const {
	return *this;
}

void CircleCollShape::SetCenter(Vector2f center) {

	Center = center;
}
void CircleCollShape::MoveCollider(Vector2f vec) {
	Center += vec;
}
void CircleCollShape::Resize(float resizeValue) {
	Radius *= resizeValue;
}