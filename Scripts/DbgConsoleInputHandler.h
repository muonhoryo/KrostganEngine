#pragma once

#include <PlayerInputManager.h>
#include <UserInterfaceManager.h>

using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class DbgConsoleInputHandler final : public IPriorityInputHandler {
	public:
		DbgConsoleInputHandler();
		virtual ~DbgConsoleInputHandler();

		void Update(const CallbackRecArgs_Upd& args) override;

		static inline const string DBG_CONSOLE_UI_NAME = "DbgConsole";
		static inline const string DBG_CONSOLE_TEXTFIELD_NAME = "DbgConsoleField";

		/// <summary>
		/// Return true if debug-console is active
		/// </summary>
		/// <returns></returns>
		static bool GetDbgConsoleStats() { return IsConsoleActive; }

	protected:
		void StartHandling_Action() override;
		void AbortHandling_Action() override;

	private:
		UIElement* DebugConsoleUI = nullptr;
		UIText* DebugConsoleTextField = nullptr;
		string Input = string();

		void TurnOnConsoleUI();
		void TurnOffConsoleUI();

		static inline bool IsConsoleActive = false;
	};
}