
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

GameObject::GameObject(const Texture& RenTexture, Vector2f RenOffset = Vector2f(0, 0), Vector2f Position = Vector2f(0, 0), float Size = 1)
	:SingleSprite(RenTexture, Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution, RenOffset, Position, Size),
	IPhysicalObject() {}

bool GameObject::IsCollide(AABBCollShape coll) {
	const ColliderShape& shape = GetCollider();
	return shape.IsOverlap(coll);
}
bool GameObject::IsCollide(CircleCollShape coll) {
	const ColliderShape& shape = GetCollider();
	return shape.IsOverlap(coll);
}
bool GameObject::IsCollide(ColliderShape* coll[], size_t count) {
	int index = 0;
	while (index < count) {
		if (IsCollideShape(*coll[index]))
			return true;
	}
	return false;
}