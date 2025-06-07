#pragma once

#include <SingleSprite.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Physics.h>

using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::UI;

namespace KrostganEngine::GameObjects {
	class GameObject :public SingleSprite,  public DynamicPhysObject {
	public:
		void SetPosition(Vector2f position) override;
		void SetScale(float scale) override;

		static inline const PhysicsLayer SOLID_COLLISION_LAYER = (PhysicsLayer)
			((size_t)PhysicsLayer::Environment |
			(size_t)PhysicsLayer::Decorations |
			(size_t)PhysicsLayer::Buildings |
			(size_t)PhysicsLayer::Units |
			(size_t)PhysicsLayer::Items);
	protected:
		GameObject(const Texture& RenTexture, Vector2f RenOffset=Vector2f(0,0), Vector2f Position = Vector2f(0, 0), float Size = 1, Color SprColor = Color::White);

		virtual const ColliderShape& GetCollider() const = 0;
	};
}