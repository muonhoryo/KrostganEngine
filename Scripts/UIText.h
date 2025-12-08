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
			const string&	textStr,
			const string*	Name			= nullptr,
			unsigned int	characterSize	= DEFAULT_FONTSIZE,
			Shader*			RendShader		= nullptr,
			std::byte		RendLayer		= DEFAULT_RENDLAYER_UI);

		UIText(
			const string&		textStr,
			const string*		Name			= nullptr,
			unsigned int		characterSize	= DEFAULT_FONTSIZE,
			Shader*				RendShader		= nullptr,
			std::byte			RendLayer		= DEFAULT_RENDLAYER_UI);

		Color	GetColor() const override;
		void	SetColor(Color color) override;

		const String& GetString() const;

		void	SetFont(const Font& font);
		void	SetString(const string& str);

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
		Text* text;
		RenderStates	RenderSt;
		Shader* RendShader;
	};
}