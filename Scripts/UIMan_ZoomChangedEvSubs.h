#pragma once

#include <Engine.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class UIMan_ZoomChangedEvSubs : public IEventSubscriber<const Engine::ViewZoomChangedEvArgs> {
	public:
		UIMan_ZoomChangedEvSubs(UIElement& userInterface)
			:userInterface(userInterface) {

		}

		void Execute(const Engine::ViewZoomChangedEvArgs& args) override {
			userInterface.SetGlobalUISize(userInterface.GetGlobalUISize()*args.OldZoom/args.NewZoom);
			Vector2f glScale = userInterface.GetGlobalScale();
			glScale /= args.OldZoom;
			glScale *= args.NewZoom;
			userInterface.SetGlobalScale(glScale);
		}

	private:
		UIElement& userInterface;
	};
}