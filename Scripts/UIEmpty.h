#pragma once

#include <UIElement.h>

using namespace sf;

namespace KrostganEngine::UI {
	/// <summary>
	/// Empty UI-element. Can be used for grouping other UI-elements.
	/// </summary>
	class UIEmpty final : public UIElement {

	public:
		UIEmpty(UIElement* Parent, Vector2f UISize = DEFAULT_SCALE)
				:UIElement(
					ctor_InitOwner(),
					Parent,
					UISize,
					DEFAULT_RENDLAYER)
		{}

		UIEmpty(Vector2f UISize = DEFAULT_SCALE)
				:UIElement(
					ctor_InitOwner(),
					UISize,
					DEFAULT_RENDLAYER)
		{}

	protected:
		void RenderGraphicAction(RenderWindow& window) override{}

	private:
		Transformable& ctor_InitOwner() {
			Owner_ = new Transformable();
			return *Owner_;
		}

		Transformable* Owner_;
	};
}