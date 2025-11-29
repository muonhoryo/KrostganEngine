#pragma once

#include <PlayerInputManager.h>

namespace KrostganEngine::PlayerControl {

	class BaseAppInputHandler : public IWindowInputHandler {

	public:
		BaseAppInputHandler();
		virtual ~BaseAppInputHandler() {}
		void Update(const CallbackRecArgs_Upd& args) override;
	};
}