
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
	Vector2f		LocalPosition,
	Vector2f		LocalScale,
	Vector2f		Anchor,
	char			RendLayer)
		:UIElement(
			ctor_InitOwner(textStr,characterSize),
			Parent,
			LocalPosition,
			LocalScale,
			0,
			Anchor,
			ctor_GetUISize(textStr,characterSize)),
		ICallbackRec_GraphPostRen(RendLayer)
{} 

UIText::UIText(
	UIElement*			Parent,
	const string		textStr,
	unsigned int		characterSize,
	Vector2f			LocalPosition,
	float				LocalScale,
	Vector2f			Anchor,
	char				RendLayer)
		:UIText(
			Parent,
			textStr,
			characterSize,
			LocalPosition,
			Vector2f(LocalScale,LocalScale),
			Anchor,
			RendLayer)
{}

UIText::UIText(
	const string		textStr,
	unsigned int		characterSize,
	Vector2f			GlobalPosition,
	Vector2f			GlobalScale,
	Vector2f			Anchor,
	char				RendLayer)
		:UIElement(
			ctor_InitOwner(textStr,characterSize),
			GlobalPosition,
			GlobalScale,
			0,
			Anchor,
			ctor_GetUISize(textStr,characterSize)),
		ICallbackRec_GraphPostRen(RendLayer)
{}

UIText::UIText(
	const string		textStr,
	unsigned int		characterSize,
	Vector2f			GlobalPosition,
	float				GlobalScale,
	Vector2f			Anchor,
	char				RendLayer)
		:UIText(
			textStr,
			characterSize,
			GlobalPosition,	
			Vector2f(GlobalScale,GlobalScale),
			Anchor,
			RendLayer)
{}

void UIText::RenderGraphicAction(RenderWindow& window) {
	window.draw(*text);
	UpdateEffects();
}
Color	UIText::GetColor() const {
	return text->getFillColor();
}
void	UIText::SetColor(Color color) {
	text->setFillColor(color);
}
void	UIText::SetFont(const Font& font) {
	text->setFont(font);
}