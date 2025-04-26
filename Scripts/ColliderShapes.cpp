
#include <Extensions.h>
#include <EngineCore.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Core;

bool ColliderShape::IsOverlap_CircleVsCircle(CircleCollShape coll1, CircleCollShape coll2) {
	float dist = VectExts::SquareLength(coll1.Center - coll2.Center);
	float minDist = coll1.Radius + coll2.Radius;
	minDist *= minDist;
	float diff = minDist - dist;
	return diff >= Engine::GetGlobalConsts().EPS;
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
			dist = VectExts::Length(nearP - coll1.Center);
		}
		return (coll1.Radius - dist)>=Engine::GetGlobalConsts().EPS;
	}
}
bool ColliderShape::IsOverlap_AABBvsAABB(AABBCollShape coll1, AABBCollShape coll2) {
	return coll2.Min.x < coll1.Max.x &&
		coll1.Min.x < coll2.Max.x &&
		coll2.Min.y < coll1.Max.y &&
		coll1.Min.y < coll2.Max.y;
}