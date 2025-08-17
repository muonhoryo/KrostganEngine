#pragma once

#include <Engine.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::UI {
	class UIMan_WinResizeEvSubs : public IEventSubscriber<Engine::WindowResizeEvArgs> {
	public:
		UIMan_WinResizeEvSubs(UIElement& userInterface) 
			:userInterface(userInterface){

		}

		void Execute(const Engine::WindowResizeEvArgs& args) override {
			userInterface.SetGlobalUISize((Vector2f)args.NewSize);
		}

	private:
		UIElement& userInterface;
	};
}