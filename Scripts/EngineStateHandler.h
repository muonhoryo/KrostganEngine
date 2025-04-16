#pragma once

#include <EngineCore.h>

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

				KrostganEngine::Core::MainMenuMode* MainMenuSt;
				KrostganEngine::Core::GameMode* GameSt;
				KrostganEngine::Core::LevelDeserializationMode* LevelDeserSt;
			};

			EngineStateHandler();
		};
	}
}