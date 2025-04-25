#pragma once

#include <EngineModes.h>

namespace KrostganEngine {
	namespace Core {
		enum EngineState {
			None,
			MainMenu,
			Game,
			LevelDeserialization
		};
		struct EngineStateHandler {

			EngineState CurrState;
			EngineState NextState;
			bool NeedToInterrupt;

			union {

				MainMenuMode* MainMenuSt;
				GameMode* GameSt;
				LevelDeserializationMode* LevelDeserSt;
			};

			EngineStateHandler();
		};
	}
}