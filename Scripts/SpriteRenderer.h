#pragma once

#include <SFML/Graphics.hpp>
#include <VisualEffectsSystem.h>
#include <WorldTransfObj.h>
#include <ICallbackRec_GraphRen.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Visual {
	class SpriteRenderer :public virtual ICallbackRec_GraphRen, public IColoredObject, public WorldTransfObj {
	public:
		SpriteRenderer(const Texture& RenTexture, Shader* RendShader = nullptr);

		SpriteRenderer(const Texture& RenTexture, float maxSizeInPixels, Shader* RendShader = nullptr);

		SpriteRenderer(const Texture& RenTexture, WorldTransfObj& Parent, Shader* RendShader = nullptr);

		SpriteRenderer(const Texture& RenTexture, WorldTransfObj& Parent, float maxSizeInPixels, Shader* RendShader = nullptr);

		virtual ~SpriteRenderer(){}

		const Texture&	GetRenTexture() const;
		float			GetSpriteMinMaxRatio() const;
		/// <summary>
		/// Return greatest size of sprite in pixels on render screen
		/// </summary>
		/// <returns></returns>
		float			GetMaxSpritePixSize() const;
		/// <summary>
		/// Return least size of sprite in pixels on render screen
		/// </summary>
		/// <returns></returns>
		float			GetMinSpritePixSize() const;
		bool			IsSpriteVertical() const;
		Shader*			GetShader() const;

		void	SetColor(Color color) override;
		Color	GetColor() const override;

		void	RenderGraphicAction(RenderWindow& window) override;

	protected:
		void		ctor_Initialize(const Texture& renTexture, float maxSizeInPixels);
		Sprite&		ctor_InitOwner();

		Vector2f	GetTextureCenter(const Texture& tex) const {
			Vector2u texSize = tex.getSize();
			return Vector2f((float)texSize.x / 2, (float)texSize.y / 2);
		}

	private:
		Sprite*			RenSprite;
		float			MinMaxSizeRatio = 1;
		bool			IsVertical;
		float			TextureResizingCoef = 1;
		RenderStates	RenderSt;
		Shader*			RendShader;

		float GetSpritePixSize(bool isMax) const;
	};
}