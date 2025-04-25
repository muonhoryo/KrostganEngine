#pragma once

#include <EngineCallbacks.h>
#include <SpriteRenderer.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine {
	namespace GameObjects {
		class GameObject :public SpriteRenderer {
		public:
			Vector2f GetPosition();
			float GetSize();
			void SetPosition(Vector2f position);
			void SetSize(float size);
		protected:
			Vector2f Position;
			float Size;
			GameObject(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position,float Size);
		};
	}
}