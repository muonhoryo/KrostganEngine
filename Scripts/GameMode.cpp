
#include <EngineModes.h>
#include <Engine.h>
#include <EngineWorkCycleModule.h>
#include <LevelBypassMap.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;


GameMode::GameMode() :EngineMode() {

    Window = &Engine::GetRenderWindow();
    BaseInputHandl = new BaseInputHandler();
    EntitiesCtrlHandler = new EntitiesCtrlInputHandler();
    GameInterface = new GameUI();

    Engine::SetCameraPos(Vector2f(0, 0));

    UserInterfaceLoader::Load_GameUI();
}
GameMode::~GameMode() {
	delete BaseInputHandl;
    delete EntitiesCtrlHandler;
    delete GameInterface;

    EngineCallbackHandler<ICallbackRec_GraphRen>& renMod = Engine::GetRenderModule();
    Engine::GetUpdateModule().Unload();
    Engine::GetLateUpdModule().Unload();
    renMod.Unload();
    Engine::GetPhysicsEngine().Unload();
    LevelBypassMapManager::Unload();
    ObjectsCatalog::Unload();
    EntitiesObserver::Unload();

    UserInterfaceManager::Initialize();
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetLateUpdModule().Execute();
    Engine::GetRenderModule().Execute();
}
