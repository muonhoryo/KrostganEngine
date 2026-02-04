
#include <ColliderShapes.h>
#include <CollectionsExts.h>
#include <VectExts.h>
#include <_Debug.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Debug;

PolygonCollShape::PolygonCollShape(vector<Vector2f>& Points)
	:Points(Points),
	BoundCircle(CircleCollShape(Vector2f(0,0), 0)) {

	if (Points.size() <= 2)
		throw exception("Invalid argument");

	InitBoundCircles();

	new PolygonColliderVisualizer(*this);

	//TODO:
	//Check intersections of lines
}
PolygonCollShape::~PolygonCollShape() {
	delete& Points;
}
void PolygonCollShape::InitBoundCircles() {

	//Calculate center
	Vector2f sum;
	for (auto& point : Points) {
		sum += point;
	}
	sum /= (float)Points.size();
	BoundCircle.Center = sum;

	//Calculate radiuses
	float max = FLT_MIN;
	float dist;
	Vector2f dir;
	for (auto& point : Points) {

		dir = point - BoundCircle.Center;
		dist = SquareLength(dir);
		if (dist > max)
			max = dist;
	}
	BoundCircle.Radius = sqrt((double)max);
}

ColliderShape& PolygonCollShape::Clone() const {

	vector<Vector2f>& newPoints = *new vector<Vector2f>(Points.size());
	CollectionsExts::Clone(Points, newPoints);
	return *new PolygonCollShape(newPoints);
}

bool PolygonCollShape::Intersect(const CircleCollShape& collision) const {
	return Intersect_PolygonVsCircle(*this, collision);
}
bool PolygonCollShape::Intersect(const AABBCollShape& collision) const {
	return Intersect_PolygonVsAABB(*this, collision);
}
bool PolygonCollShape::Intersect(const PolygonCollShape& objShape) const {
	return Intersect_PolygonVsPolygon(objShape, *this);
}
bool PolygonCollShape::Intersect(const ColliderShape* coll[], size_t count)const {

	int index = 0;
	while (index < count) {
		if (coll[index]->Intersect(*this))
			return true;
	}
	return false;
}

Vector2f PolygonCollShape::GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {
	
	//TODO
	//Currently is not wanted

	throw exception("Unimplemented method");
	return subjShape.Center;
}
Vector2f PolygonCollShape::GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {

	//TODO
	//Currently is not wanted

	throw exception("Unimplemented method");
	return subjShape.GetCenter();
}
Vector2f PolygonCollShape::GetCollisionResolvPoint(const PolygonCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const {

	//TODO
	//Currently is not wanted

	throw exception("Unimplemented method");
	return subjShape.GetOutterBoundCircle().Center;
}

bool PolygonCollShape::IsPointInCollider(Vector2f point) const {

	Vector2f a = Points[Points.size() - 1];
	Vector2f b;
	for (int i = 0;i < Points.size();++i) {
		b = Points[i];
		if (GetDimRelToLine_Left(a, b, point))
			return false;

		a = b;
	}
	return false;
}
Vector2f PolygonCollShape::GetClosestPoint(Vector2f point)const {
	
	//TODO
	//Curently is not wanted

	throw exception("Unimplemented method");
	return point;
}
bool PolygonCollShape::IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest = false) const {

	//TODO
	//Curently is not wanted

	throw exception("Unimplemented method");
	return false;
}
bool PolygonCollShape::IntersectSegment(const Segment& segm) const {

	//TODO
	//Curently is not wanted

	throw exception("Unimplemented method");
	return false;
}

const CircleCollShape& PolygonCollShape::GetOutterBoundCircle()const {
	return BoundCircle;
}

void PolygonCollShape::SetCenter(Vector2f center) {

	//TODO
	//Currently is not wanted

	cout << "WARNING: Unimplemented method" << endl;
}
void PolygonCollShape::MoveCollider(Vector2f vec) {

	//TODO
	//Currently is not wanted

	throw exception("Unimplemented method");
}
void PolygonCollShape::Resize(float resizeValue) {
	
	//TODO
	//Currenty is not wanted

	throw exception("Unimplemented method");
}

const vector<Vector2f>& PolygonCollShape::GetPoints() const {
	return Points;
}