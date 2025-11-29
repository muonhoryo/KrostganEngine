#pragma once

#include <PlayerInputManager.h>

namespace KrostganEngine::PlayerControl {
	class MainMenuTransitionHandler :public IBaseInputHandler {

	public:
		MainMenuTransitionHandler(){

		}
		virtual ~MainMenuTransitionHandler() {
		}

		void Update(const CallbackRecArgs_Upd& args) override;

		bool		HasPressed = false;
	};
}