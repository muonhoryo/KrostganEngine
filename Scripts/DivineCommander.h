#pragma once

namespace KrostganEngine::Debug {
	class DivineCommander {
	public:
		static void TurnOn();
		static void TurnOff();

		static bool GetActivity() {
			return IsActive;
		}

	private:
		DivineCommander(){}

		static inline  bool IsActive = false;
	};
}