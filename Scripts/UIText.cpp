
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

UIText::UIText(
	UIElement*		Parent,
	const string	textStr,
	unsigned int	characterSize,
	Vector2f		GlobalPosition,
	Vector2f		LocalScale,
	Vector2f		Anchor)
		:UIElement(
			ctor_InitOwner(textStr,characterSize),
			Parent,
			GlobalPosition,
			LocalScale,
			Anchor,
			ctor_GetUISize(textStr,characterSize))
{
	auto par = GetParent();
	auto owner = text;
	Vector2f pos = GetGlobalPosition();
} 

UIText::UIText(
	UIElement*			Parent,
	const string		textStr,
	unsigned int		characterSize,
	Vector2f			GlobalPosition,
	float				LocalScale,
	Vector2f			Anchor)
		:UIText(
			Parent,
			textStr,
			characterSize,
			GlobalPosition,
			Vector2f(LocalScale,LocalScale),
			Anchor)
{}

UIText::UIText(
	const string		textStr,
	unsigned int		characterSize,
	Vector2f			GlobalPosition,
	Vector2f			GlobalScale,
	Vector2f			Anchor)
		:UIElement(
			ctor_InitOwner(textStr,characterSize),
			GlobalPosition,
			GlobalScale,
			Anchor,
			ctor_GetUISize(textStr,characterSize))
{}

UIText::UIText(
	const string		textStr,
	unsigned int		characterSize,
	Vector2f			GlobalPosition,
	float				GlobalScale,
	Vector2f			Anchor)
		:UIText(
			textStr,
			characterSize,
			GlobalPosition,
			Vector2f(GlobalScale,GlobalScale),
			Anchor)
{}

void UIText::RenderGraphic(RenderWindow& window) {
	window.draw(*text);
}
Color	UIText::GetColor() const {
	return text->getFillColor();
}
void	UIText::SetColor(Color color) {
	text->setFillColor(color);
}