
#include <ICallbackRec_GraphRen.h>
#include <SpriteRenderer.h>
#include <SFML/Graphics.hpp>
#include <Engine.h>
#include <iostream>
#include <Extensions.h>

using namespace sf;
using namespace KrostganEngine::UI;
using namespace KrostganEngine::Core;

SpriteRenderer::SpriteRenderer(const Texture& RenTexture, Vector2f Offset, Color SprColor) :
	SpriteRenderer(RenTexture, (float)max(RenTexture.getSize().x, RenTexture.getSize().y), Offset)
{}
SpriteRenderer::SpriteRenderer(const Texture& RenTexture, float maxSizeInPixels, Vector2f Offset, Color SprColor) :
	ICallbackRec_GraphRen() {
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
	SetSpriteColor(SprColor);
	this->Offset = Offset;
}

void SpriteRenderer::RenderGraphic(RenderWindow& window) {
	window.draw(RenSprite);
}

const Texture& SpriteRenderer::GetRenTexture() {
	return *RenSprite.getTexture();
}
Vector2f SpriteRenderer::GetSpriteOffset() {
	return Offset;
}
Vector2f SpriteRenderer::GetSpriteGlobalPosition() {
	return RenSprite.getPosition();
}
Vector2f SpriteRenderer::GetSpriteInharitedPosition() {
	return  GetSpriteGlobalPosition()-GetSpriteOffset();
}
float SpriteRenderer::GetSpriteMinMaxRatio() {
	return MinMaxSizeRatio;
}
bool SpriteRenderer::IsSpriteVertical() {
	return IsVertical;
}
float SpriteRenderer::GetMaxSpritePixSize() {
	if (IsVertical) {
		return RenSprite.getTexture()->getSize().y* RenSprite.getScale().y;
	}
	else {
		return RenSprite.getTexture()->getSize().x * RenSprite.getScale().x;
	}
}
float SpriteRenderer::GetMinSpritePixSize() {
	if (IsVertical) {
		return RenSprite.getTexture()->getSize().x * RenSprite.getScale().x;
	}
	else {
		return RenSprite.getTexture()->getSize().y * RenSprite.getScale().y;
	}
}
Vector2f SpriteRenderer::GetSpriteSize() {
	return MainSize;
}
Color SpriteRenderer::GetSpriteColor() {
	return RenSprite.getColor();
}

void SpriteRenderer::SetSpriteOffset(Vector2f offset) {
	Vector2f inharPos = GetSpriteInharitedPosition();
	Offset = offset;
	SetSpriteInharitedPosition(inharPos);
}
void SpriteRenderer::ResizeSprite(Vector2f size) {
	Vector2f newScale = size * TextureResizingMult;
	RenSprite.setScale(newScale);
	MainSize = size;
}
void SpriteRenderer::SetSpriteColor(Color color) {
	RenSprite.setColor(color);
}

void SpriteRenderer::SetSpriteInharitedPosition(Vector2f position) {
	RenSprite.setPosition(position + GetSpriteOffset());
}