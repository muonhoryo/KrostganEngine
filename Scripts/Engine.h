#pragma once

#include <SFML/Graphics.hpp>
#include <EngineModes.h>
#include <EngineStateHandler.h>
#include <EngineWorkCycleModule.h>
#include <ExternalConfigurations.h>
#include <Physics.h>

using namespace sf;
using namespace KrostganEngine::Physics;

namespace KrostganEngine {
	namespace Core {
		 class Engine {
			 
		 public:
			static Engine& GetInstance();
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
			static PhysicsEngine& GetPhysicsEngine();
			static const EngineConfig& GetEngineConfig();
			static const GlobalConsts& GetGlobalConsts();
			static const ExternalGlobalResources& GetGlobalResources();
			static float GetZoom();

			static Vector2f ScreenPosToGlobalCoord(const Vector2f& screenPos);
			static Vector2u GetScreenSize();

			static const std::string ENGINE_VERSION;
		 private:
			Engine();
			static void InitializeSystems();
			static Engine* Singleton;
			EngineStateHandler EngStateHandler;
			EngineMode* CurrMode;
			EngineRenderModule& RenderModule;
			EngineUpdateModule& UpdateModule;
			PhysicsEngine& PhysicsEng;
			const EngineConfig* EngineConfiguration;
			const GlobalConsts* Consts;
			const ExternalGlobalResources* GlobalResources;

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