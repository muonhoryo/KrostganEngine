#pragma once

#include <SFML/Graphics.hpp>
#include <EngineModes.h>
#include <EngineStateHandler.h>
#include <EngineWorkCycleModule.h>
#include <ExternalData.h>
#include <Physics.h>
#include <CursorManager.h>

#define eps Engine::GetGlobalConsts().EPS

using namespace sf;
using namespace KrostganEngine::UI;
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
			static void SetCameraPos(Vector2f pos);
			static void MoveCamera(Vector2f movVal);

			static RenderWindow& GetRenderWindow();
			static float GetFrameDeltaTime();
			static float GetFrameRenderTime();
			static bool IsNeedToInterrupt();
			static EngineState GetCurrentEngState();
			static EngineState GetNextEngState();
			static EngineRenderModule& GetRenderModule();
			static EngineUpdateModule& GetUpdateModule();
			static EngineLateUpdateModule& GetLateUpdModule();
			static PhysicsEngine& GetPhysicsEngine();
			static CursorManager& GetCursorManager();
			static const EngineConfig& GetEngineConfig();
			static const GlobalConsts& GetGlobalConsts();
			static const ExternalGlobalResources& GetGlobalResources();

			static float GetZoom();
			static Vector2f GetCameraPos();
			static Vector2f ScreenPosToGlobalCoord(const Vector2f& screenPos);
			static Vector2u GetScreenSize();
			static Vector2f GetCursorClampedPos();
			static bool IsMouseOnScreen();
			static bool IsMouseOnScreen(Vector2i mousePos);
			static bool HasWindowFocus();

			static const std::string ENGINE_VERSION;
		 private:
			Engine();
			void InitializeSystems();
			void InitializeCursorManager();
			static inline Engine* Singleton=nullptr;
			EngineStateHandler EngStateHandler;
			EngineMode* CurrMode;
			EngineRenderModule& RenderModule;
			EngineUpdateModule& UpdateModule;
			EngineLateUpdateModule& LateUpdateModule;
			PhysicsEngine& PhysicsEng;
			CursorManager* WindCursorManager;
			const EngineConfig* EngineConfiguration;
			const GlobalConsts* Consts;
			const ExternalGlobalResources* GlobalResources;

			RenderWindow RendWin;
			/// <summary>
			/// In seconds
			/// </summary>
			float FrameDeltaTime = 0;
			/// <summary>
			/// In seconds
			/// </summary>
			float FrameRenderTime = 0;
			float Zoom = 1;

			static void RequestToChangeState(EngineState state);
			static void SetMode_MainMenu();
			static void SetMode_Game();
			static void SetMode_LevelDeser();
			static void ResolveInterruption();
			static void ResetInterruption();

			static EngineMode* GetCurrentEngMode();
			static View& InstanceNewView();

			friend static void EngineUpdateModule::SetFrameDeltaTime(float time);
			friend static void EngineRenderModule::SetFrameRenderTime(float time);
		};
	}
}