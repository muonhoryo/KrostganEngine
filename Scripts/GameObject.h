#pragma once

#include <SingleSprite.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Physics.h>

using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::UI;

namespace KrostganEngine::GameObjects {
	class GameObject :public SingleSprite, public IPhysicalObject {
	public:
		bool IsCollide(AABBCollShape coll) const override;
		bool IsCollide(CircleCollShape coll) const override;
		bool IsCollide(ColliderShape* coll[], size_t count) const override;
		bool IsInCollider(Vector2f point) const override;
	protected:
		GameObject(const Texture& RenTexture, Vector2f RenOffset=Vector2f(0,0), Vector2f Position = Vector2f(0, 0), float Size = 1, Color SprColor = Color::White);

		virtual const ColliderShape& GetCollider() const = 0;
		virtual bool IsCollideShape(const ColliderShape& shape) const = 0;
	};
}