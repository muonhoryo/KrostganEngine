#pragma once

#include <UIElement.h>

using namespace sf;

namespace KrostganEngine::UI {
	/// <summary>
	/// Empty UI-element. Can be used for grouping other UI-elements.
	/// </summary>
	class UIEmpty : public UIElement {

	public:
		UIEmpty(UIElement* Parent, const string* Name = nullptr, Vector2f UISize = DEFAULT_SCALE)
				:UIElement(
					ctor_InitOwner(),
					Parent,
					Name,
					UISize,
					DEFAULT_RENDLAYER)
		{}

		UIEmpty(const string* Name = nullptr, Vector2f UISize = DEFAULT_SCALE)
				:UIElement(
					ctor_InitOwner(),
					Name,
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