
#include <EngineModes.h>
#include <Engine.h>
#include <EngineWorkCycleModule.h>
#include <LevelBypassMap.h>
#include <GameLevel.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Visual;


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

    EngineCallbackHandler<ICallbackRec_GraphRen>& renMod = Engine::GetRenderModule();
    Engine::GetUpdateModule().Unload();
    Engine::GetLateUpdModule().Unload();
    renMod.Unload();
    Engine::GetPhysicsEngine().Unload();
    LevelBypassMapManager::Unload();
    ObjectsCatalog::Unload();
    EntitiesObserver::Unload();
    LevelManager::UnassignLevelInfo();

    PlayerInputManager::Clear();
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetLateUpdModule().Execute();
    Engine::GetRenderModule().Execute();
}
