#pragma once

#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <EngineModes.h>
#include <EngineStateHandler.h>
#include <EngineWorkCycleModule.h>

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

			static void SetZoom(float zoom);

			static RenderWindow& GetRenderWindow();
			static float GetFrameTime();
			static bool IsNeedToInterrupt();
			static EngineState GetCurrentEngState();
			static EngineState GetNextEngState();
			static EngineRenderModule& GetRenderModule();
			static EngineUpdateModule& GetUpdateModule();
			static float GetZoom();
		 private:
			Engine();
			static void InitializeSystems();
			static Engine* Singleton;
			EngineStateHandler EngStateHandler;
			EngineMode* CurrMode;
			EngineRenderModule& RenderModule;
			EngineUpdateModule& UpdateModule;

			RenderWindow RendWin;
			float FrameTime=0;
			float Zoom = 1;

			static void RequestToChangeState(EngineState state);
			static void SetMode_MainMenu();
			static void SetMode_Game();
			static void SetMode_LevelDeser();
			static void ResolveInterruption();
			static void ResetInterruption();

			static EngineMode* GetCurrentEngMode();
			static View& InstanceNewView();

			friend static float SetFrameTime();
		};
	}
}