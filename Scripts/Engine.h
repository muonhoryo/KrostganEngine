#pragma once

#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <EngineModes.h>

using namespace sf;

namespace KrostganEngine {
	namespace Core {
		 class Engine {
			 
		 public:
			 struct EngineStateHandler;
			 enum EngineState;

		 public:
			static const std::string ENGINE_VERSION;
			static Engine& GetInstanceEngine();
			static void StartEngine();

			static void ReqToSetMode_MainMenu();
			static void ReqToSetMode_Game();

			static RenderWindow& GetRenderWindow();
			static float GetFrameTime();
		private:
			Engine();
			static Engine* Singleton;
			static Engine::EngineStateHandler EngStateHandler;
			static EngineMode* CurrMode;

			RenderWindow RendWin;
			float FrameTime=0;

			static void RequestToChangeState(EngineState state);
			static void SetMode_MainMenu();
			static void SetMode_Game();
			static void ResolveInterruption();

			friend static float SetFrameTime();
		};
	}
}