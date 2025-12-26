
#include <ColliderShapes.h>
#include <Extensions.h>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine;

AABBCollShape::AABBCollShape(Vector2f Min,Vector2f Max)
{
	if (Min.x > Max.x ||
		Min.y > Max.y)
		throw std::exception("Incorrect params of AABB shape");

	this->Min = Min;
	this->Max = Max;
}

ColliderShape& AABBCollShape::Clone() const {

	return *new AABBCollShape(Min, Max);
}

AABBCollShape& AABBCollShape::InstanceBy_CenterAndSize(Vector2f center, float width, float height) {

	width *= 0.5;
	height *= 0.5;
	Vector2f min = center;
	Vector2f max = center;
	min.x -= width;
	min.y -= height;
	max.x += width;
	max.y += height;
	return *new AABBCollShape(min, max);
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

Vector2f AABBCollShape::GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {

	Vector2f neaPnt = GetClosestPoint(subjShape.Center);
	if (SquareLength(neaPnt - subjShape.Center) > subjShape.Radius * subjShape.Radius)
		return subjShape.Center;

	Vector2f dir;
	float len;
	if (IsPointInCollider(subjShape.Center)) {

		dir = neaPnt - subjShape.Center;
		len = Length(dir) + subjShape.Radius;
	}
	else {

		dir = subjShape.Center - neaPnt;
		len = subjShape.Radius - Length(dir);
	}
	dir = Normalize(dir);
	dir = Vector2f(dir.x * len, dir.y * len);
	return subjShape.Center + dir;

		////UNWORKING CODE OF COLLISION NON-SLIDING RESOLVING

		//Vector2i intersDir;
		//{
		//	size_t mask =		//opposite corner mask
		//		(subjMovDir.x > 0 ? 0 : 1) |
		//		(subjMovDir.y > 0 ? 0 : 2); 
		//	Vector2f cornr = GetCornerByMask(mask);		//get opposite to movdir corner
		//	Vector2f diff = Vector2f(abs(cornr.x - subjShape.Center.x), abs(cornr.y - subjShape.Center.y));		//Get differencies between corner and center
		//	Vector2f size = GetSize();
		//	diff = Vector2f(diff.x / size.x, diff.y / size.y);		//calculate proportional differencies
		//	bool isXmoreY = diff.x > diff.y;
		//	intersDir = Vector2i(
		//		isXmoreY ? ((mask & 1) == 0 ? 1 : -1):0,
		//		!isXmoreY ? ((mask & 2) == 0 ? 1 : -1):0);
		//}
		//Vector2f anch = subjShape.Center + (Vector2f(intersDir.x * subjShape.Radius, intersDir.y * subjShape.Radius));
		//Segment intersSide = Segment(
		//	Vector2f(
		//		(intersDir.x > 0) ? Max.x : Min.x,
		//		(intersDir.y < 0) ? Min.y : Max.y),
		//	Vector2f(
		//		(intersDir.x < 0) ? Min.x : Max.x,
		//		(intersDir.x > 0) ? Max.y : Min.y));	

		//Vector2f rayPnt;
		//if (Engine::GetPhysicsEngine().Intersect(Ray(anch,-subjMovDir), intersSide, &rayPnt)) {

		//	return rayPnt - anch;
		//}
		//else {

		//	Vector2f circlPnt;
		//	Vector2f corner;
		//	Vector2f maxInterResolvVec;
		//	Vector2f interResolvVec;
		//	float maxDist_sqr=-1;
		//	float dist_sqr;
		//	for (size_t i = 0;i < 4;i++) {

		//		corner = GetCornerByMask(i);
		//		if (subjShape.IntersectRay(Ray(corner, subjMovDir), &circlPnt, true)) {
		//			
		//			interResolvVec = corner - circlPnt;
		//			dist_sqr = SquareLength(interResolvVec);
		//			if (dist_sqr > maxDist_sqr) {
		//				maxInterResolvVec = interResolvVec;
		//				maxDist_sqr = dist_sqr;
		//			}
		//		}
		//	}
		//	if (maxDist_sqr < 0)
		//		return subjShape.Center;
		//	else
		//		return subjShape.Center + maxInterResolvVec;
		//}
}
Vector2f AABBCollShape::GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir,bool isSlideColl)const {
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	//NEED TO FIX
	return Vector2f(1, 0);
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
bool AABBCollShape::IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest) const {
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
bool AABBCollShape::IntersectSegment(const Segment& segm) const {
	
	if (IsPointInCollider(segm.First) || IsPointInCollider(segm.Second))
		return true;

	Segment segm2(Vector2f(0,0),Vector2f(0,0));
	Vector2f pnt;

	segm2.First = GetCornerByMask(0);
	segm2.Second = GetCornerByMask(1);
	if (PhysicsEngine::Intersect(segm, segm2, &pnt))
		return true;

	segm2.First = GetCornerByMask(1);
	segm2.Second = GetCornerByMask(3);
	if (PhysicsEngine::Intersect(segm, segm2, &pnt))
		return true;

	segm2.First = GetCornerByMask(3);
	segm2.Second = GetCornerByMask(2);
	if (PhysicsEngine::Intersect(segm, segm2, &pnt))
		return true;

	segm2.First = GetCornerByMask(2);
	segm2.Second = GetCornerByMask(0);
	if (PhysicsEngine::Intersect(segm, segm2, &pnt))
		return true;

	return false;
}

CircleCollShape AABBCollShape::GetBoundedCircle()const {
	Vector2f size = GetSize();
	size *= 0.5f;
	return CircleCollShape(GetCenter(), Length(size));
}

void AABBCollShape::MoveCollider(Vector2f vec) {

	Min += vec;
	Max += vec;
}
void AABBCollShape::Resize(float resizeValue) {

	Vector2f center = GetCenter();
	float x = center.x - Min.x;
	x *= resizeValue;
	float y = center.y - Min.y;
	y *= resizeValue;
	Min.x = center.x - x;
	Min.y = center.y - y;
	Max.x = center.x + x;
	Max.y = center.y + y;
}

Vector2f AABBCollShape::GetCenter() const {
	return Vector2f((Min.x + Max.x) * 0.5f, (Min.y + Max.y) * 0.5f);
}
Vector2f AABBCollShape::GetCornerByMask(size_t mask) const {
	return Vector2f(
		((mask & 1) == 0) ? Min.x : Max.x,
		((mask & 2) == 0) ? Min.y : Max.y);
}
Vector2f AABBCollShape::GetSize() const {
	return Vector2f(Max.x - Min.x, Max.y - Min.y);
}