#pragma once

#include <SpriteRenderer.h>
#include <TransformableObj.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class SingleSprite :public SpriteRenderer,public TransformableObj {

	public:
		SingleSprite(const Texture& RenTexture, float maxSpriteSize, Vector2f RenOffset=Vector2f(0,0), Vector2f Position = Vector2f(0, 0), float Size = 1, Color SprColor = Color::White);

		void SetPosition(Vector2f position) override;
		void SetScale(float scale) override;
	};
}