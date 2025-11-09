
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

UISprite::UISprite(const Texture& RenTexture, Shader* RendShader, byte RendLayer)
		:UIElement(ctor_InitOwner(), (Vector2f)RenTexture.getSize(), RendLayer),
		RendShader(RendShader)
{
	ctor_Initialize(RenTexture);
}

UISprite::UISprite(const Texture& RenTexture, UIElement* Parent,Shader*	RendShader, byte RendLayer)
		:UIElement(ctor_InitOwner(), Parent, (Vector2f)RenTexture.getSize(), RendLayer),
		RendShader(RendShader)
{
	ctor_Initialize(RenTexture);
}

UISprite::~UISprite() {

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