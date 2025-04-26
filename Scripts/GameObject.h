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
		bool IsCollide(AABBCollShape coll) override;
		bool IsCollide(CircleCollShape coll) override;
		bool IsCollide(ColliderShape* coll[], size_t count) override;
	protected:
		GameObject(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position, float Size);

		virtual const ColliderShape& GetCollider() const = 0;
		virtual bool IsCollideShape(const ColliderShape& shape) const = 0;
	};
}