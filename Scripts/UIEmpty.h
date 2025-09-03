#pragma once

#include <UIElement.h>

using namespace sf;

namespace KrostganEngine::UI {
	/// <summary>
	/// Empty UI-element. Can be used for grouping other UI-elements.
	/// </summary>
	class UIEmpty final : public UIElement {

	public:
		UIEmpty(
			UIElement*		Parent,
			Vector2f		LocalPosition	= DEFAULT_POSITION,
			Vector2f		LocalScale		= DEFAULT_SCALE,
			Vector2f		Anchor			= DEFAULT_ANCHOR,
			Vector2f		UISize			= DEFAULT_SCALE)
				:UIElement(
					ctor_InitOwner(),
					Parent,
					LocalPosition,
					LocalScale,
					Anchor,
					UISize)
		{}

		UIEmpty(
			UIElement*			Parent,
			Vector2f			LocalPosition	= DEFAULT_POSITION,
			float				LocalScale		= 1,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Vector2f			UISize			= DEFAULT_SCALE)
				:UIElement(
					ctor_InitOwner(),
					Parent,
					LocalPosition,
					LocalScale,
					Anchor,
					UISize)
		{}

		UIEmpty(
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			GlobalScale		= DEFAULT_SCALE,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Vector2f			UISize			= DEFAULT_SCALE)
				:UIElement(
					ctor_InitOwner(),
					GlobalPosition,
					GlobalScale,
					Anchor,
					UISize)
		{}

	protected:
		void RenderGraphicAction(RenderWindow& window){}

	private:
		Transformable& ctor_InitOwner() {
			Owner_ = new Transformable();
			return *Owner_;
		}

		Transformable* Owner_;
	};
}