#pragma once

#include <SpriteRenderer.h>

using namespace sf;

namespace KrostganEngine::Visual {
	class IndicatorFill : public SpriteRenderer {

	public:
		IndicatorFill(
			const Texture&	RenTexture,
			const Texture&	MaskTexture,
			Shader&			RendShader,
			float			maxSpriteSize,
			Vector2f		GlobalPosition = DEFAULT_POSITION,
			float			GlobalScale = DEFAULT_SCALE_SNG,
			Color			SprColor = Color::White);
		IndicatorFill(
			const Texture&		RenTexture,
			const Texture&		MaskTexture,
			WorldTransfObj&		Parent,
			Shader&				RendShader,
			float				maxSpriteSize,
			Vector2f			LocalPosition = DEFAULT_POSITION,
			float				LocalScale = DEFAULT_SCALE_SNG,
			Color				SprColor = Color::White);

		void	SetFillness(float fillness);
		float	GetFillness() const;

		void RenderGraphicAction(RenderWindow& window) override;

	private:
		float Fillness = 1;
		const Texture& MaskTexture;

		static const inline string SHAD_PARAM_NAME_FILLNESS		= "mask_threshold";
		static const inline string SHAD_PARAM_NAME_MASK			= "mask"; 
	};
}