#pragma once

#include <SpriteRenderer.h>
#include <TransformableObj.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class SingleSprite :public SpriteRenderer,public TransformableObj {

	public:
		SingleSprite(const Texture& RenTexture, float maxSpriteSize, Vector2f RenOffset,
			Vector2f Position, float Size);

		void SetPosition(Vector2f position) override;
		void SetScale(float scale) override;
	};
}