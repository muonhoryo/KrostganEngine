#pragma once

#include <PrimitiveCollisions.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::Physics;

CircleCollision::CircleCollision(Vector2f& Center, float& Radius, PhysicsLayer& Layer):
Center(Center),Radius(Radius),Layer(Layer){
}

PhysicsLayer CircleCollision::GetLayer() {
	return Layer;
}

bool CircleCollision::IsCollide(AABB coll) {
	Circle cirl = Circle(Center, Radius);
	return coll.IsOverlap(cirl);
}
bool CircleCollision::IsCollide(Circle coll) {
	Circle cirl = Circle(Center, Radius);
	return coll.IsOverlap(cirl);
}
bool CircleCollision::IsCollide(ColliderShape* coll[], size_t count) {
	int index = 0;
	Circle cirl = Circle(Center, Radius);
	while (index < count) {
		if (coll[index]->IsOverlap(cirl))
			return true;
	}
	return false;
}