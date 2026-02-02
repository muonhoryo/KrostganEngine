
#include <EngineModes.h>
#include <Engine.h>
#include <EngineWorkCycleModule.h>
#include <LevelBypassMap.h>
#include <_GameLevel.h>
#include <WarFogStencilGen.h>
#include <_Debug.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::Debug;

GameMode::GameMode() :EngineMode() {

    new CameraControlInputHan();
    new BaseAppInputHandler();
    new EntitiesCtrlInputHandler();

    GameInterface = new ExtVisualManager();

    Engine::SetCameraPos(Vector2f(0, 0));

    UserInterfaceLoader::Load_GameUI();
}
GameMode::~GameMode() {
    delete GameInterface;

    Engine::UnloadCallbacksModules();
    LevelBypassMapManager::Unload();
    WorldObjsCatalog::Unload();
    EntitiesObserver::Unload();
    LevelManager::UnassignLevelInfo();
    GroupSelectionSystem::Clear();
    PlayerInputManager::Clear();
    delete WarFogStencilGen::GetInstance();
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetLateUpdModule().Execute();
    Engine::GetRenderModule().Execute();
}
