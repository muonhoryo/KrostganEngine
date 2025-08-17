
#include <SpriteRenderer.h>
#include <Engine.h>
#include <iostream>
#include <Extensions.h>

using namespace sf;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::Core;

//
//
//ctors
//
//

void SpriteRenderer::ctor_Initialize(const Texture& renTexture,float maxSizeInPixels) {

	if (RendShader != nullptr)
		RenderSt.shader = RendShader;

	RenSprite->setTexture(renTexture);
	Vector2u size = renTexture.getSize();
	if (size.x < size.y) {
		MinMaxSizeRatio = (float)size.x / (float)size.y;
		IsVertical = true;
	}
	else {
		MinMaxSizeRatio = (float)size.y / (float)size.x;
		IsVertical = false;
	}
	TextureResizingCoef = maxSizeInPixels / max(size.x, size.y);

}
Sprite& SpriteRenderer::ctor_InitOwner() {
	RenSprite = new Sprite();
	return *RenSprite;
}

SpriteRenderer::SpriteRenderer(
	const Texture&	RenTexture,
	Vector2f		GlobalPosition,
	Vector2f		GlobalScale,
	Color			SprColor,
	Shader*			RendShader)
		
	:SpriteRenderer(
		RenTexture,
		(float)max(RenTexture.getSize().x, RenTexture.getSize().y),
		GlobalPosition,
		GlobalScale,
		SprColor,
		RendShader)
{}

SpriteRenderer::SpriteRenderer(
	const Texture&	RenTexture, 
	float			maxSizeInPixels,
	Vector2f		GlobalPosition,
	Vector2f		GlobalScale,
	Color			SprColor,
	Shader*			RendShader) 
		:TransformableObj(ctor_InitOwner(), GlobalPosition, GlobalScale, ctor_GetOrigin(RenTexture)),
		RendShader	(RendShader){

	ctor_Initialize(RenTexture,maxSizeInPixels);

	SetGlobalScale(GlobalScale*TextureResizingCoef);
	SetGlobalPosition(GlobalPosition);
	SetColor(SprColor);
}

SpriteRenderer::SpriteRenderer(
	const Texture&		RenTexture,
	TransformableObj&	Parent,
	Vector2f			GlobalPosition,
	Vector2f			LocalScale,
	Color				SprColor,
	Shader*				RendShader)
	
	:SpriteRenderer(
		RenTexture,
		Parent,
		(float)max(RenTexture.getSize().x,RenTexture.getSize().y),
		GlobalPosition,
		LocalScale,
		SprColor,
		RendShader)
{}

SpriteRenderer::SpriteRenderer(
	const Texture& RenTexture,
	TransformableObj& Parent,
	float				maxSizeInPixels,
	Vector2f			GlobalPosition,
	Vector2f			LocalScale,
	Color				SprColor,
	Shader*				RendShader)
		:TransformableObj(ctor_InitOwner(),Parent, GlobalPosition,LocalScale,ctor_GetOrigin(RenTexture)),
		RendShader(RendShader) {

	ctor_Initialize(RenTexture, maxSizeInPixels);

	SetLocalScale(LocalScale * TextureResizingCoef);
	SetGlobalPosition(GlobalPosition);
	SetColor(SprColor);
}

SpriteRenderer::~SpriteRenderer() {
	delete RenSprite;
}

void SpriteRenderer::RenderGraphic(RenderWindow& window) {

	window.draw(*RenSprite, RenderSt);
	UpdateEffects();
}

//
//
//getters
//
//

const Texture& SpriteRenderer::GetRenTexture() const {
	return *RenSprite->getTexture();
}
float			SpriteRenderer::GetSpriteMinMaxRatio() const {
	return MinMaxSizeRatio;
}
bool			SpriteRenderer::IsSpriteVertical() const {
	return IsVertical;
}

float			SpriteRenderer::GetMaxSpritePixSize() const {
	return GetSpritePixSize(true);
}
float	SpriteRenderer::GetMinSpritePixSize() const {
	return GetSpritePixSize(false);
}
float	SpriteRenderer::GetSpritePixSize(bool isMax) const {
	Vector2f scale = RenSprite->getScale();
	if (IsVertical == isMax) {

		return RenSprite->getTexture()->getSize().y * scale.y;
	}
	else {

		return RenSprite->getTexture()->getSize().x * scale.x;
	}
}

Color		SpriteRenderer::GetColor() const {
	return RenSprite->getColor();
}
Shader*		SpriteRenderer::GetShader() const {
	return RendShader;
}

//
//
//override methods
//
//

void	SpriteRenderer::SetColor		(Color color) {
	RenSprite->setColor(color);
}