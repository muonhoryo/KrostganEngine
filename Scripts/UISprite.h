#pragma once

#include <UIElement.h>
#include <ICallbackRec_GraphPostRen.h>
#include <VisualEffectsSystem.h>

using namespace KrostganEngine::Visual;

namespace KrostganEngine::UI {
	class UISprite : public UIElement, public virtual IColoredObject{
	public:
		UISprite(
			const Texture&	RenTexture,
			Vector2f		GlobalPosition	= DEFAULT_POSITION,
			Vector2f		GlobalScale		= DEFAULT_SCALE,
			Vector2f		Anchor			= DEFAULT_ANCHOR,
			Color			SprColor		= Color::White,
			Shader*			RendShader		= nullptr,
			char			RendLayer		= 0);
		
		UISprite(
			const Texture&	RenTexture,
			Vector2f		GlobalPosition	= DEFAULT_POSITION,
			float			GlobalScale		= 1,
			Vector2f		Anchor			= DEFAULT_ANCHOR,
			Color			SprColor		= Color::White,
			Shader*			RendShader		= nullptr,
			char			RendLayer		= 0);

		UISprite(
			const Texture&	RenTexture,
			UIElement*		Parent,
			Vector2f		LocalPosition	= DEFAULT_POSITION,
			Vector2f		LocalScale		= DEFAULT_SCALE,
			Vector2f		Anchor			= DEFAULT_ANCHOR,
			Color			SprColor		= Color::White,
			Shader*			RendShader		= nullptr,
			char			RendLayer		= 0);
		
		UISprite(
			const Texture&	RenTexture,
			UIElement*		Parent,
			Vector2f		LocalPosition	= DEFAULT_POSITION,
			float			LocalScale		= 1,
			Vector2f		Anchor			= DEFAULT_ANCHOR,
			Color			SprColor		= Color::White,
			Shader*			RendShader		= nullptr,
			char			RendLayer		= 0);
		
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
		/*Vector2f	ctor_GetOrigin(const Texture& tex) const {
			Vector2u texSize = tex.getSize();
			return Vector2f((float)texSize.x / 2, (float)texSize.y / 2);
		}*/

	private:
		Sprite*			RenSprite;
		RenderStates	RenderSt;
		Shader*			RendShader;
	};
}