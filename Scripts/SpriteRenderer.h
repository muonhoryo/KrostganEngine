#pragma once

#include <ICallbackRec_GraphRen.h>
#include <SFML/Graphics.hpp>
#include <VisualEffectsSystem.h>

using namespace sf;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Visual {
	class SpriteRenderer :public ICallbackRec_GraphRen, public IColoredObject{
	public:
		SpriteRenderer(
			const Texture&	RenTexture, 
			Vector2f		offset		=	Vector2f(0,0), 
			Color			SprColor	=	Color::White,
			Shader*			RendShader	=	nullptr);

		SpriteRenderer(
			const Texture&	RenTexture, 
			float			maxSizeInPixels, 
			Vector2f		offset				=	Vector2f(0,0), 
			Color			SprColor			=	Color::White,
			Shader*			RendShader			=	nullptr);

		void RenderGraphic(RenderWindow& window) override;

		const Texture&	GetRenTexture				() const;
		Vector2f		GetSpriteOffset				() const;
		Vector2f		GetSpriteGlobalPosition		() const;
		Vector2f		GetSpriteInharitedPosition	() const;
		float			GetSpriteMinMaxRatio		() const;
		float			GetMaxSpritePixSize			() const;
		float			GetMinSpritePixSize			() const;
		Vector2f		GetSpriteSize				() const;
		bool			IsSpriteVertical			() const;
		Shader*			GetShader					() const;
		
		void	SetSpriteOffset(Vector2f offset);
		void	ResizeSprite(Vector2f maxSize);

		void			SetColor(Color color) override;
		Color			GetColor() const override;
	protected:
		void SetSpriteInharitedPosition(Vector2f position);
	private:
		Sprite			RenSprite;
		Vector2f		Offset;
		float			MinMaxSizeRatio;
		bool			IsVertical;
		float			TextureResizingMult;
		Vector2f		MainSize;
		RenderStates	RenderSt;
		Shader*			RendShader;
	};
}