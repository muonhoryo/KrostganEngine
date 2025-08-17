#pragma once

#include <SFML/Graphics.hpp>
#include <VisualEffectsSystem.h>
#include <TransformableObj.h>
#include <ICallbackRec_GraphRen.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Visual {
	class SpriteRenderer :public virtual ICallbackRec_GraphRen, public IColoredObject, public TransformableObj {
	public:
		SpriteRenderer(
			const Texture& RenTexture,
			Vector2f		GlobalPosition = Vector2f(0, 0),
			Vector2f		GlobalScale = DEFAULT_SCALE,
			Color			SprColor = Color::White,
			Shader* RendShader = nullptr);

		SpriteRenderer(
			const Texture& RenTexture,
			float			maxSizeInPixels,
			Vector2f		GlobalPosition = Vector2f(0, 0),
			Vector2f		GlobalScale = DEFAULT_SCALE,
			Color			SprColor = Color::White,
			Shader* RendShader = nullptr);

		SpriteRenderer(
			const Texture& RenTexture,
			TransformableObj& Parent,
			Vector2f			GlobalPosition = Vector2f(0, 0),
			Vector2f			LocalScale = DEFAULT_SCALE,
			Color				SprColor = Color::White,
			Shader* RendShader = nullptr);

		SpriteRenderer(
			const Texture& RenTexture,
			TransformableObj& Parent,
			float				maxSizeInPixels,
			Vector2f			GlobalPosition = Vector2f(0, 0),
			Vector2f			LocalScale = DEFAULT_SCALE,
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

		void	RenderGraphic(RenderWindow& window) override;

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