#pragma once

#include <UIElement.h>
#include <SFML/Graphics.hpp>
#include <CoreVisual.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace sf;

namespace KrostganEngine::UI {
	class UIText :public UIElement, public virtual IColoredObject {
	public:
		UIText(
			UIElement*		Parent,
			const string	textStr			= "",
			unsigned int	characterSize	= 30,
			Vector2f		GlobalPosition = DEFAULT_POSITION,
			Vector2f		LocalScale = DEFAULT_SCALE,
			Vector2f		Anchor = DEFAULT_ANCHOR);

		UIText(
			UIElement*			Parent,
			const string		textStr			= "",
			unsigned int		characterSize	= 30,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				LocalScale		= 1,
			Vector2f			Anchor			= DEFAULT_ANCHOR);

		UIText(
			const string		textStr			= "",
			unsigned int		characterSize	= 30,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			GlobalScale		= DEFAULT_SCALE,
			Vector2f			Anchor			= DEFAULT_ANCHOR);

		UIText(
			const string		textStr			= "",
			unsigned int		characterSize	= 30,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				GlobalScale		= 1,
			Vector2f			Anchor			= DEFAULT_ANCHOR);

		void RenderGraphic(RenderWindow& window) override;

		Color	GetColor() const override;
		void	SetColor(Color color) override;

		Text* text;
		Vector2f ScreenPosition = Vector2f(0, 0);

	protected:

		Text& ctor_InitOwner(const string& textStr, unsigned int characterSize);
		/// <summary>
		/// Init owner if he was null at function execution
		/// </summary>
		/// <param name="textStr"></param>
		/// <param name="characterSize"></param>
		/// <returns></returns>
		Vector2f ctor_GetUISize(const string& textStr, unsigned int characterSize);
	};
}