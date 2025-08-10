#pragma once

#include <ICallbackRec_GraphRen.h>
#include <SFML/Graphics.hpp>
#include <VisualEffectsSystem.h>
#include <TransformableObj.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Visual {
	class SpriteRenderer :public ICallbackRec_GraphRen, public IColoredObject,public TransformableObj {
	public:
		SpriteRenderer(
			const Texture&	RenTexture,
			Vector2f		GlobalPosition	=	Vector2f(0,0),
			Vector2f		GlobalScale		=	DEFAULT_SCALE,
			Color			SprColor		=	Color::White,
			Shader*			RendShader		=	nullptr);

		SpriteRenderer(
			const Texture&	RenTexture,
			float			maxSizeInPixels,
			Vector2f		GlobalPosition		= Vector2f(0, 0),
			Vector2f		GlobalScale			= DEFAULT_SCALE,
			Color			SprColor			=	Color::White,
			Shader*			RendShader			=	nullptr);

		SpriteRenderer(
			const Texture&		RenTexture,
			TransformableObj&	Parent,
			Vector2f			GlobalPosition	= Vector2f(0, 0),
			Vector2f			LocalScale		= DEFAULT_SCALE,
			Color				SprColor		= Color::White,
			Shader*				RendShader		= nullptr);

		SpriteRenderer(
			const Texture&		RenTexture,
			TransformableObj&	Parent,
			float				maxSizeInPixels,
			Vector2f			GlobalPosition		= Vector2f(0, 0),
			Vector2f			LocalScale			= DEFAULT_SCALE,
			Color				SprColor			= Color::White,
			Shader*				RendShader			= nullptr);

		virtual ~SpriteRenderer();

	private:
		void ctor_Initialize(const Texture& renTexture, float maxSizeInPixels);
		Sprite& ctor_InitOwner();

	public:
		void RenderGraphic(RenderWindow& window) override;

		const Texture&	GetRenTexture				() const;
		float			GetSpriteMinMaxRatio		() const;

		/// <summary>
		/// Return greatest size of sprite in pixels on render screen
		/// </summary>
		/// <returns></returns>
		float GetMaxSpritePixSize() const;
		/// <summary>
		/// Return least size of sprite in pixels on render screen
		/// </summary>
		/// <returns></returns>
		float GetMinSpritePixSize() const;

		//Vector2f GetGlobalScale() const override;
		//Vector2f GetLocalScale() const override;
		
		bool			IsSpriteVertical			() const;
		
		Shader*			GetShader					() const;
		/*
		void SetGlobalScale	(Vector2f scale) override;
		void SetLocalScale	(Vector2f scale) override;*/

		void			SetColor(Color color) override;
		Color			GetColor() const override;

	protected:
		Vector2f ctor_GetOrigin(const Texture& tex) const{
			Vector2u texSize = tex.getSize();
			return Vector2f((float)texSize.x / 2, (float)texSize.y / 2);
		}

	private:
		Sprite*			RenSprite;
		float			MinMaxSizeRatio			= 1;
		bool			IsVertical;
		float			TextureResizingCoef		= 1;
		/*Vector2f		SpriteFillSize_Local	= DEFAULT_SCALE;
		Vector2f		SpriteFillSize_Global	= DEFAULT_SCALE;*/
		RenderStates	RenderSt;
		Shader*			RendShader;

		float GetSpritePixSize(bool isMax) const;
	};
}