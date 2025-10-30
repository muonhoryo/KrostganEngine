#pragma once

namespace KrostganEngine::Debug {
	/// <summary>
	/// Generally extends entity's control
	/// 
	/// -> Allow to control enemy's and neutral's entities
	/// -> Allow to select multiple enemy's and neutral's entities
	/// </summary>
	class DBG_DivineCommander final {
	public:
		static void TurnOn();
		static void TurnOff();

		static bool GetActivity() {
			return IsActive;
		}

	private:
		DBG_DivineCommander(){}

		static inline  bool IsActive = false;
	};
}