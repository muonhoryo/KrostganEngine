
#include <IndicatorFill.h>
#include <iostream>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Visual;


IndicatorFill::IndicatorFill(
	const Texture&	RenTexture,
	const Texture&	MaskTexture,
	Shader&			RendShader,
	float			maxSpriteSize,
	Vector2f		GlobalPosition,
	float			GlobalScale,
	Color			SprColor)

	:SquareScaleSprite(RenTexture, maxSpriteSize, GlobalPosition, GlobalScale, SprColor, &RendShader),
	MaskTexture(MaskTexture)
{}
IndicatorFill::IndicatorFill(
	const Texture &		RenTexture,
	const Texture &		MaskTexture,
	WorldTransfObj &	Parent,
	Shader &			RendShader,
	float				maxSpriteSize,
	Vector2f			LocalPosition,
	float				LocalScale,
	Color				SprColor)
	:SquareScaleSprite(RenTexture,maxSpriteSize, LocalPosition,LocalScale,SprColor,&RendShader),
	MaskTexture(MaskTexture)
{}

void IndicatorFill::SetFillness(float fillness) {

	Fillness = clamp<float>(fillness, 0, 1);
}
float IndicatorFill::GetFillness() const{
	return Fillness;
}

void IndicatorFill::RenderGraphic(RenderWindow& window) {
	GetShader()->setUniform(SHAD_PARAM_NAME_MASK, MaskTexture);
	GetShader()->setUniform(SHAD_PARAM_NAME_FILLNESS, Fillness);
	SquareScaleSprite::RenderGraphic(window);
}