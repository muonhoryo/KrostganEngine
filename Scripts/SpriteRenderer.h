#pragma once

#include <EngineCallbacks.h>
#include <SFML/Graphics.hpp>
#include <ICallbackRec_GraphRen.h>

using namespace sf;

namespace KrostganEngine {
	namespace GameObjects {
		class SpriteRenderer :public ICallbackRec_GraphRen {
		public:
			void RenderGraphic(RenderWindow& window) override;
			const Texture& GetRenTexture();
			void SetOffset(Vector2f offset);
			Vector2f GetOffset();
			Vector2f GetGlobalPosition();
			Vector2f GetInharitedPosition();
			float GetMinMaxRatio();
			bool IsSpriteVertical();
			float GetMaxSpritePixSize();
			float GetMinSpritePixSize();
			Vector2f GetSpriteSize();
			void Resize(Vector2f maxSize);
		protected:
			void SetSpriteInharitedPosition(Vector2f position);
			SpriteRenderer(const Texture& RenTexture,Vector2f offset);
			SpriteRenderer(const Texture& RenTexture, float maxSizeInPixels, Vector2f offset);
		private:
			Sprite RenSprite;
			Vector2f Offset;
			float MinMaxSizeRatio;
			bool IsVertical;
			float TextureResizingMult;
			Vector2f MainSize;
		};
	}
}