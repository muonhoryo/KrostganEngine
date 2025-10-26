#pragma once

#include <UIElement.h>
#include <SFML/Graphics.hpp>
#include <IColoredObject.h>

#define DEFAULT_FONTSIZE 30u

using namespace std;
using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::UI {
	class UIText :public UIElement, public virtual IColoredObject {
	public:
		UIText(
			UIElement*		Parent,
			const string	textStr			= "",
			unsigned int	characterSize	= DEFAULT_FONTSIZE,
			Vector2f		LocalPosition	= DEFAULT_POSITION,
			Vector2f		LocalScale		= DEFAULT_SCALE,
			Vector2f		Anchor			= DEFAULT_ANCHOR,
			Shader*			RendShader		= nullptr,
			byte			RendLayer		= DEFAULT_RENDLAYER_UI);

		UIText(
			UIElement*			Parent,
			const string		textStr			= "",
			unsigned int		characterSize	= DEFAULT_FONTSIZE,
			Vector2f			LocalPosition	= DEFAULT_POSITION,
			float				LocalScale		= 1,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Shader*				RendShader		= nullptr,
			byte				RendLayer		= DEFAULT_RENDLAYER_UI);

		UIText(
			const string		textStr			= "",
			unsigned int		characterSize	= DEFAULT_FONTSIZE,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			GlobalScale		= DEFAULT_SCALE,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Shader*				RendShader		= nullptr,
			byte				RendLayer		= DEFAULT_RENDLAYER_UI);

		UIText(
			const string		textStr			= "",
			unsigned int		characterSize	= DEFAULT_FONTSIZE,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				GlobalScale		= DEFAULT_SCALE_SNG,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Shader*				RendShader		= nullptr,
			byte				RendLayer		= DEFAULT_RENDLAYER_UI);

		Color	GetColor() const override;
		void	SetColor(Color color) override;

		void	SetFont(const Font& font);

		Text* text;
		Vector2f ScreenPosition = Vector2f(0, 0);

	protected:

		void RenderGraphicAction(RenderWindow& window) override;

		Text&		ctor_InitOwner(const string& textStr, unsigned int characterSize);
		/// <summary>
		/// Init owner if he was null at function execution
		/// </summary>
		/// <param name="textStr"></param>
		/// <param name="characterSize"></param>
		/// <returns></returns>
		Vector2f	ctor_GetUISize(const string& textStr, unsigned int characterSize);
		void		ctor_Initialize();

	private:
		RenderStates	RenderSt;
		Shader* RendShader;
	};
}