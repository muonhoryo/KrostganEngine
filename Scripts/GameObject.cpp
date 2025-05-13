
#include <GameObject.h>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <Extensions.h>
#include <Engine.h>
#include <TransformableObj.h>

using namespace std;
using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

GameObject::GameObject(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position , float Size ,Color SprColor)
	:SingleSprite(RenTexture, Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution, RenOffset, Position, Size,SprColor),
	IPhysicalObject() {}

bool GameObject::IsCollide(AABBCollShape coll)const {
	const ColliderShape& shape = GetCollider();
	return shape.Intersect(coll);
}
bool GameObject::IsCollide(CircleCollShape coll) const{
	const ColliderShape& shape = GetCollider();
	return shape.Intersect(coll);
}
bool GameObject::IsCollide(ColliderShape* coll[], size_t count) const{
	int index = 0;
	while (index < count) {
		if (IsCollideShape(*coll[index]))
			return true;
	}
	return false;
}
bool GameObject::IsInCollider(Vector2f point) const{
	const ColliderShape& shape = GetCollider();
	return shape.IsPointInCollider(point);
}