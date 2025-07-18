
#pragma once

#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::PlayerControl {

	class PlayerInputManager {

	public:
		/// <summary>
		/// Return true if reserved button
		/// </summary>
		static bool GetBtnState_Escape();
		static void SetBtnState_Escape(bool newState);

	private:
		PlayerInputManager(){}

		static inline bool IsReservedBtn_Escape = false;
		static inline bool FreeBtn_Escape = false;
		static inline Clock ReservBtnDelay_Escape;
	};
}