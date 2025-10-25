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
		SpriteRenderer(
			const Texture& RenTexture,
			Vector2f		GlobalPosition = DEFAULT_POSITION,
			float			GlobalScale = DEFAULT_SCALE_SNG,
			float			GlobalRotation = 0,
			Color			SprColor = Color::White,
			Shader* RendShader = nullptr);

		SpriteRenderer(
			const Texture& RenTexture,
			float			maxSizeInPixels,
			Vector2f		GlobalPosition = DEFAULT_POSITION,
			float			GlobalScale = DEFAULT_SCALE_SNG,
			float			GlobalRotation = 0,
			Color			SprColor = Color::White,
			Shader* RendShader = nullptr);

		SpriteRenderer(
			const Texture&		RenTexture,
			WorldTransfObj&		Parent,
			Vector2f			LocalPosition = DEFAULT_POSITION,
			float				LocalScale = DEFAULT_SCALE_SNG,
			float				LocalRotation = 0,
			Color				SprColor = Color::White,
			Shader* RendShader = nullptr);

		SpriteRenderer(
			const Texture&		RenTexture,
			WorldTransfObj&		Parent,
			float				maxSizeInPixels,
			Vector2f			LocalPosition = DEFAULT_POSITION,
			float				LocalScale = DEFAULT_SCALE_SNG,
			float				LocalRotation = 0,
			Color				SprColor = Color::White,
			Shader* RendShader = nullptr);

		virtual ~SpriteRenderer();

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
		Vector2f	ctor_GetOrigin(const Texture& tex) const {
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