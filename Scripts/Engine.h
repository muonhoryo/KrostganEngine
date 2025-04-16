#pragma once

#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <EngineModes.h>
#include <EngineStateHandler.h>

using namespace sf;

namespace KrostganEngine {
	namespace Core {
		 class Engine {
			 
		 public:
			static const std::string ENGINE_VERSION;
			static Engine& GetInstanceEngine();
			static void StartEngine();

			static void ReqToSetMode_MainMenu();
			static void ReqToSetMode_Game();
			static void ReqToSetMode_LevelDeser();

			static RenderWindow& GetRenderWindow();
			static float GetFrameTime();
			static bool IsNeedToInterrupt();
			static EngineState GetCurrentEngState();
			static EngineState GetNextEngState();
		private:
			Engine();
			static Engine* Singleton;
			EngineStateHandler EngStateHandler;
			EngineMode* CurrMode;

			RenderWindow RendWin;
			float FrameTime=0;

			static void RequestToChangeState(EngineState state);
			static void SetMode_MainMenu();
			static void SetMode_Game();
			static void SetMode_LevelDeser();
			static void ResolveInterruption();
			static void ResetInterruption();

			static EngineMode* GetCurrentEngMode();

			friend static float SetFrameTime();
		};
	}
}