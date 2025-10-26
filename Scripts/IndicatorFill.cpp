
#include <IndicatorFill.h>
#include <iostream>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Visual;


IndicatorFill::IndicatorFill(
	const Texture&	RenTexture,
	const Texture&	MaskTexture,
	Shader&			RendShader,
	float			maxSpriteSize)

	:SpriteRenderer(RenTexture, maxSpriteSize, &RendShader),
	MaskTexture(MaskTexture)
{}
IndicatorFill::IndicatorFill(
	const Texture &		RenTexture,
	const Texture &		MaskTexture,
	WorldTransfObj &	Parent,
	Shader &			RendShader,
	float				maxSpriteSize)
	:SpriteRenderer(RenTexture,maxSpriteSize, &RendShader),
	MaskTexture(MaskTexture)
{}

void IndicatorFill::SetFillness(float fillness) {

	Fillness = clamp<float>(fillness, 0, 1);
}
float IndicatorFill::GetFillness() const{
	return Fillness;
}

void IndicatorFill::RenderGraphicAction(RenderWindow& window) {
	GetShader()->setUniform(SHAD_PARAM_NAME_MASK, MaskTexture);
	GetShader()->setUniform(SHAD_PARAM_NAME_FILLNESS, Fillness);
	SpriteRenderer::RenderGraphicAction(window);
}