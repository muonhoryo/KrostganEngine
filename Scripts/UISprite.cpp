
#include <UISprite.h>
#include <Engine.h>
#include <iostream>
#include <Extensions.h>

using namespace sf;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::UI;
using namespace KrostganEngine::Core;

//
//
//ctors
//
//

void UISprite::ctor_Initialize(const Texture& renTexture) {

	if (RendShader != nullptr)
		RenderSt.shader = RendShader;

	RenSprite->setTexture(renTexture);
}
Sprite& UISprite::ctor_InitOwner() {
	RenSprite = new Sprite();
	return *RenSprite;
}

UISprite::UISprite(
	const Texture& RenTexture,
	Vector2f		GlobalPosition,
	Vector2f		GlobalScale,
	float			GlobalRotation,
	Vector2f		Anchor,
	Color			SprColor,
	Shader*			RendShader,
	byte			RendLayer)
		:UIElement(
			ctor_InitOwner(), 
			GlobalPosition, 
			GlobalScale, 
			GlobalRotation,
			Anchor,
			(Vector2f)RenTexture.getSize(),
			RendLayer),
		RendShader(RendShader)
{
	ctor_Initialize(RenTexture);
	SetColor(SprColor);
}

UISprite::UISprite(
	const Texture& RenTexture,
	Vector2f		GlobalPosition,
	float			GlobalScale,
	float			GlobalRotation,
	Vector2f		Anchor,
	Color			SprColor,
	Shader*			RendShader,
	byte			RendLayer)
		:UISprite(
			RenTexture,
			GlobalPosition,
			Vector2f(GlobalScale,GlobalScale),
			GlobalRotation,
			Anchor,
			SprColor,
			RendShader,
			RendLayer)
{}

UISprite::UISprite(
	const Texture&		RenTexture,
	UIElement*			Parent,
	Vector2f			LocalPosition,
	Vector2f			LocalScale,
	float				LocalRotation,
	Vector2f			Anchor,
	Color				SprColor,
	Shader*				RendShader,
	byte				RendLayer)
		:UIElement(
			ctor_InitOwner(), 
			Parent, 
			LocalPosition,
			LocalScale, 
			LocalRotation,
			Anchor,
			(Vector2f)RenTexture.getSize(),
			RendLayer),
		RendShader(RendShader)
{
	ctor_Initialize(RenTexture);
	SetColor(SprColor);
}

UISprite::UISprite(
	const Texture&	RenTexture,
	UIElement*		Parent,
	Vector2f		LocalPosition,
	float			LocalScale,
	float			LocalRotation,
	Vector2f		Anchor,
	Color			SprColor,
	Shader*			RendShader,
	byte			RendLayer)
		:UISprite(
			RenTexture,
			Parent,
			LocalPosition,
			Vector2f(LocalScale,LocalScale),
			LocalRotation,
			Anchor,
			SprColor,
			RendShader,
			RendLayer)
{}

UISprite::~UISprite() {
	delete RenSprite;
}

void UISprite::RenderGraphicAction(RenderWindow& window) {

	window.draw(*RenSprite, RenderSt);
	UpdateEffects();
}

//
//
//getters
//
//

const Texture& UISprite::GetRenTexture() const {
	return *RenSprite->getTexture();
}

Color			UISprite::GetColor() const {
	return RenSprite->getColor();
}
Shader*			UISprite::GetShader() const {
	return RendShader;
}

//
//
//override methods
//
//

void	UISprite::SetColor(Color color) {
	RenSprite->setColor(color);
}