
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
	float			GlobalScale,
	float			GlobalRotation,
	Color			SprColor,
	Shader*			RendShader)
		
	:SpriteRenderer(
		RenTexture,
		(float)max(RenTexture.getSize().x, RenTexture.getSize().y),
		GlobalPosition,
		GlobalScale,
		GlobalRotation,
		SprColor,
		RendShader)
{}

SpriteRenderer::SpriteRenderer(
	const Texture&	RenTexture, 
	float			maxSizeInPixels,
	Vector2f		GlobalPosition,
	float			GlobalScale,
	float			GlobalRotation,
	Color			SprColor,
	Shader*			RendShader) 
		:WorldTransfObj(ctor_InitOwner(), GlobalPosition, GlobalScale, GlobalRotation,ctor_GetOrigin(RenTexture)),
		RendShader	(RendShader){

	ctor_Initialize(RenTexture,maxSizeInPixels);

	ITransformableObj::SetGlobalScale(GlobalScale*TextureResizingCoef);
	SetColor(SprColor);
}

SpriteRenderer::SpriteRenderer(
	const Texture&		RenTexture,
	WorldTransfObj&		Parent,
	Vector2f			LocalPosition,
	float				LocalScale,
	float				LocalRotation,
	Color				SprColor,
	Shader*				RendShader)
	
	:SpriteRenderer(
		RenTexture,
		Parent,
		(float)max(RenTexture.getSize().x,RenTexture.getSize().y),
		LocalPosition,
		LocalScale,
		LocalRotation,
		SprColor,
		RendShader)
{}

SpriteRenderer::SpriteRenderer(
	const Texture& RenTexture,
	WorldTransfObj& Parent,
	float				maxSizeInPixels,
	Vector2f			LocalPosition,
	float				LocalScale,
	float				LocalRotation,
	Color				SprColor,
	Shader*				RendShader)
		:WorldTransfObj(ctor_InitOwner(),Parent, LocalPosition,LocalScale, LocalRotation,ctor_GetOrigin(RenTexture)),
		RendShader(RendShader) {

	ctor_Initialize(RenTexture, maxSizeInPixels);

	ITransformableObj::SetLocalScale(LocalScale * TextureResizingCoef);
	SetLocalPosition(LocalPosition);
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