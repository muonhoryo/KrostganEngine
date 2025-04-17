#pragma once

#include <EngineCallbacks.h>
#include <SpriteRenderer.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine {
	namespace GameObjects {
		class GameObject :SpriteRenderer {
		public:
			Vector2f GetPosition();
			void SetPosition(Vector2f position);
		protected:
			Vector2f Position;
			GameObject(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position);
		};
	}
}