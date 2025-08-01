
#include <ICallbackRec_GraphRen.h>
#include <SpriteRenderer.h>
#include <SFML/Graphics.hpp>
#include <Engine.h>
#include <iostream>
#include <Extensions.h>

using namespace sf;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::Core;

SpriteRenderer::SpriteRenderer(
	const Texture&	RenTexture, 
	Vector2f		Offset, 
	Color			SprColor,
	Shader*			RendShader)
		
	:SpriteRenderer(
		RenTexture, 
		(float)max(RenTexture.getSize().x, RenTexture.getSize().y), 
		Offset,
		SprColor,
		RendShader)
{
	
}
SpriteRenderer::SpriteRenderer(
	const Texture&	RenTexture, 
	float			maxSizeInPixels, 
	Vector2f		Offset, 
	Color			SprColor,
	Shader*			RendShader) 
		:ICallbackRec_GraphRen(),
		Offset		(Offset),
		RendShader	(RendShader){

	if (RendShader != nullptr)		
		RenderSt.shader = RendShader;

	RenSprite.setTexture(RenTexture);
	Vector2u texSize = RenTexture.getSize();
	RenSprite.setOrigin(Vector2f((float)texSize.x/2,(float)texSize.y/2));
	Vector2u size = RenTexture.getSize();
	if (size.x < size.y) {
		MinMaxSizeRatio = (float)size.x / (float)size.y;
		IsVertical = true;
	}
	else {
		MinMaxSizeRatio = (float)size.y / (float)size.x;
		IsVertical = false;
	}
	TextureResizingMult = maxSizeInPixels / GetMaxSpritePixSize();
	ResizeSprite(Vector2f(1, 1));
	SetColor(SprColor);
}

void	SpriteRenderer::RenderGraphic	(RenderWindow& window) {

	window.draw(RenSprite,RenderSt);
	UpdateEffects();
}

const Texture&	SpriteRenderer::GetRenTexture() const{
	return *RenSprite.getTexture();
}
Vector2f		SpriteRenderer::GetSpriteOffset() const{
	return Offset;
}
Vector2f		SpriteRenderer::GetSpriteGlobalPosition() const{
	return RenSprite.getPosition();
}
Vector2f		SpriteRenderer::GetSpriteInharitedPosition() const{
	return  GetSpriteGlobalPosition()-GetSpriteOffset();
}
float			SpriteRenderer::GetSpriteMinMaxRatio() const{
	return MinMaxSizeRatio;
}
bool			SpriteRenderer::IsSpriteVertical() const{
	return IsVertical;
}
float			SpriteRenderer::GetMaxSpritePixSize() const{
	if (IsVertical) {
		return RenSprite.getTexture()->getSize().y* RenSprite.getScale().y;
	}
	else {
		return RenSprite.getTexture()->getSize().x * RenSprite.getScale().x;
	}
}
float			SpriteRenderer::GetMinSpritePixSize() const{
	if (IsVertical) {
		return RenSprite.getTexture()->getSize().x * RenSprite.getScale().x;
	}
	else {
		return RenSprite.getTexture()->getSize().y * RenSprite.getScale().y;
	}
}
Vector2f		SpriteRenderer::GetSpriteSize() const{
	return MainSize;
}
Color			SpriteRenderer::GetColor() const{
	return RenSprite.getColor();
}
Shader*			SpriteRenderer::GetShader() const {
	return RendShader;
}

void	SpriteRenderer::SetSpriteOffset	(Vector2f offset) {
	Vector2f inharPos = GetSpriteInharitedPosition();
	Offset = offset;
	SetSpriteInharitedPosition(inharPos);
}
void	SpriteRenderer::ResizeSprite	(Vector2f size) {
	Vector2f newScale = size * TextureResizingMult;
	RenSprite.setScale(newScale);
	MainSize = size;
}
void	SpriteRenderer::SetColor		(Color color) {
	RenSprite.setColor(color);
}

void SpriteRenderer::SetSpriteInharitedPosition(Vector2f position) {
	RenSprite.setPosition(position + GetSpriteOffset());
}