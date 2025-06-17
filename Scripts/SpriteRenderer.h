#pragma once

#include <ICallbackRec_GraphRen.h>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Visual {
	class SpriteRenderer :public ICallbackRec_GraphRen {
	public:
		SpriteRenderer(const Texture& RenTexture, Vector2f offset=Vector2f(0,0), Color SprColor = Color::White);
		SpriteRenderer(const Texture& RenTexture, float maxSizeInPixels, Vector2f offset=Vector2f(0,0), Color SprColor = Color::White);

		void RenderGraphic(RenderWindow& window) override;

		const Texture& GetRenTexture();
		Vector2f GetSpriteOffset();
		Vector2f GetSpriteGlobalPosition();
		Vector2f GetSpriteInharitedPosition();
		float GetSpriteMinMaxRatio();
		float GetMaxSpritePixSize();
		float GetMinSpritePixSize();
		Vector2f GetSpriteSize();
		bool IsSpriteVertical();
		Color GetSpriteColor();

		void SetSpriteOffset(Vector2f offset);
		void ResizeSprite(Vector2f maxSize);
		virtual void SetSpriteColor(Color color);
	protected:
		void SetSpriteInharitedPosition(Vector2f position);
	private:
		Sprite RenSprite;
		Vector2f Offset;
		float MinMaxSizeRatio;
		bool IsVertical;
		float TextureResizingMult;
		Vector2f MainSize;
	};
}