
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
	Vector2f		Anchor,
	Color			SprColor,
	Shader*			RendShader,
	char			RendLayer)
		:UIElement(
			ctor_InitOwner(), 
			GlobalPosition, 
			GlobalScale, 
			Anchor,
			(Vector2f)GetRenTexture().getSize(),
			RendLayer),
		RendShader(RendShader)
{
	ctor_Initialize(RenTexture);

	//SetGlobalScale(GlobalScale );
	//SetGlobalPosition(GlobalPosition);
	SetColor(SprColor);
}

UISprite::UISprite(
	const Texture& RenTexture,
	Vector2f		GlobalPosition,
	float			GlobalScale,
	Vector2f		Anchor,
	Color			SprColor,
	Shader*			RendShader,
	char			RendLayer)
		:UISprite(
			RenTexture,
			GlobalPosition,
			Vector2f(GlobalScale,GlobalScale),
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
	Vector2f			Anchor,
	Color				SprColor,
	Shader*				RendShader,
	char				RendLayer)
		:UIElement(
			ctor_InitOwner(), 
			Parent, 
			LocalPosition,
			LocalScale, 
			Anchor,
			(Vector2f)GetRenTexture().getSize(),
			RendLayer),
		RendShader(RendShader)
{
	ctor_Initialize(RenTexture);

	//SetLocalScale(LocalScale );
	//SetGlobalPosition(GlobalPosition);
	SetColor(SprColor);
}

UISprite::UISprite(
	const Texture&	RenTexture,
	UIElement*		Parent,
	Vector2f		LocalPosition,
	float			LocalScale,
	Vector2f		Anchor,
	Color			SprColor,
	Shader*			RendShader,
	char			RendLayer)
		:UISprite(
			RenTexture,
			Parent,
			LocalPosition,
			Vector2f(LocalScale,LocalScale),
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