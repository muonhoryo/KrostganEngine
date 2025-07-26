#pragma once

#include <SingleSprite.h>

using namespace sf;

namespace KrostganEngine::Visual {
	class IndicatorFill : public SingleSprite {

	public:
		IndicatorFill(
			const Texture&	RenTexture,
			const Texture&	MaskTexture,
			Shader&			RendShader,
			float			maxSpriteSize,
			Vector2f		RenOffset = Vector2f(0, 0),
			Vector2f		Position = Vector2f(0, 0),
			float			Size = 1,
			Color			SprColor = Color::White);

		void	SetFillness(float fillness);
		float	GetFillness() const;

		void RenderGraphic(RenderWindow& window) override;

	private:
		float Fillness = 1;
		const Texture& MaskTexture;

		static const inline string SHAD_PARAM_NAME_FILLNESS		= "mask_threshold";
		static const inline string SHAD_PARAM_NAME_MASK			= "mask"; 
	};
}