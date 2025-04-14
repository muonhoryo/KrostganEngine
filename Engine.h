#pragma once

#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <EngineModes.h>

using namespace sf;

namespace KrostganEngine {
	namespace Core {
		 class Engine {

		 public:
			 struct EngineState {
				 enum StateType {
					 None,
					 MainMenu,
					 Game
				 };

				 EngineState() {
					 CurrState = None;
					 NextState = None;
					 NeedToInterrupt = false;
				 }

				 StateType CurrState=None;
				 StateType NextState=None; 
				 bool NeedToInterrupt=false;

				 union {

					 KrostganEngine::Core::MainMenuMode MainMenuSt;
					 KrostganEngine::Core::GameMode GameSt;
				 };
			 };

		 public:
			static const std::string ENGINE_VERSION;
			static Engine& GetInstanceEngine();

			static void ReqToSetMode_MainMenu();
			static void ReqToSetMode_Game();

			static RenderWindow& GetRenderWindow();
			static float GetFrameTime();
		private:
			Engine();
			static Engine* Singleton;
			static Engine::EngineState EngState;
			static EngineMode* EngMode;

			RenderWindow RendWin;
			float FrameTime=0;

			static void RequestToChangeState(EngineState::StateType state);
			static void SetMode_MainMenu();
			static void SetMode_Game();
			static void ResolveInterruption();

			friend static float SetFrameTime();
		};
	}
}