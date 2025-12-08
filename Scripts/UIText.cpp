
#include <UIText.h>
#include <Engine.h>

using namespace KrostganEngine::UI;
using namespace KrostganEngine;
using namespace sf;

Text& UIText::ctor_InitOwner(const string& textStr,  unsigned int characterSize) {
	
	if (text != nullptr)
		return *text;

	text = new Text(textStr, ExternalGlobalResources::Get_DefaultFont(),characterSize);
	return *text;
}
Vector2f UIText::ctor_GetUISize(const string& textStr, unsigned int characterSize) {
	auto& txt = ctor_InitOwner(textStr, characterSize);
	auto bounds = txt.getGlobalBounds();
	return Vector2f(bounds.width, bounds.height);
}
void		UIText::ctor_Initialize() {

	if (RendShader != nullptr)
		RenderSt.shader = RendShader;
}

UIText::UIText(
	UIElement*		Parent,
	const string&	textStr,
	const string*	Name,
	unsigned int	characterSize,
	Shader*			RendShader,
	std::byte		RendLayer)
		:UIElement(
			ctor_InitOwner(textStr,characterSize),
			Parent,
			Name,
			ctor_GetUISize(textStr,characterSize),
			RendLayer),
		RendShader(RendShader)
{}

UIText::UIText(
	const string&		textStr,
	const string*		Name,
	unsigned int		characterSize,
	Shader*				RendShader,
	std::byte			RendLayer)
		:UIElement(
			ctor_InitOwner(textStr,characterSize),
			Name,
			ctor_GetUISize(textStr,characterSize),
			RendLayer),
	RendShader(RendShader)
{}

void UIText::RenderGraphicAction(RenderWindow& window) {
	window.draw(*text,RenderSt);
	UpdateEffects();
}
Color	UIText::GetColor() const {
	return text->getFillColor();
}
void	UIText::SetColor(Color color) {
	text->setFillColor(color);
}

const String& UIText::GetString() const {
	return text->getString();
}

void	UIText::SetFont(const Font& font) {
	text->setFont(font);
}
void	UIText::SetString(const string& str) {
	text->setString(str);
}