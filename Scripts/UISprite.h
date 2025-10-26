#pragma once

#include <UIElement.h>
#include <VisualEffectsSystem.h>

using namespace KrostganEngine::Visual;

namespace KrostganEngine::UI {
	class UISprite : public UIElement, public virtual IColoredObject{
	public:
		UISprite(
			const Texture&	RenTexture,
			Shader*			RendShader		= nullptr,
			byte			RendLayer		= DEFAULT_RENDLAYER_UI);
		
		UISprite(
			const Texture&	RenTexture,
			UIElement*		Parent,
			Shader*			RendShader		= nullptr,
			byte			RendLayer		= DEFAULT_RENDLAYER_UI);
		
		virtual ~UISprite();

	public:
		const Texture&	GetRenTexture() const;
		Shader*			GetShader() const;

		void			SetColor(Color color) override;
		Color			GetColor() const override;

	protected:
		void	RenderGraphicAction(RenderWindow& window) override;

		void		ctor_Initialize(const Texture& renTexture);
		Sprite&		ctor_InitOwner();

	private:
		Sprite*			RenSprite;
		RenderStates	RenderSt;
		Shader*			RendShader;
	};
}