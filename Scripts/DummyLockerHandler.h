#pragma once

#include <PlayerInputManager.h>

namespace KrostganEngine::PlayerControl {
	/// <summary>
	/// Used for locking base input without any actions.
	/// For example: End game's screens
	/// </summary>
	class DummyLockerHandler final : public IPriorityInputHandler {

	public:
		DummyLockerHandler(){}
		virtual ~DummyLockerHandler(){}

		void Update(const CallbackRecArgs_Upd& args) override {}
	};
}