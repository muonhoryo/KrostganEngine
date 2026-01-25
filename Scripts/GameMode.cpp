
#include <EngineModes.h>
#include <Engine.h>
#include <EngineWorkCycleModule.h>
#include <LevelBypassMap.h>
#include <GameLevel.h>
#include <WarFogStencilGen.h>
#include <Debug.h>

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

    //Create object's debug-visualizer
    //ATTENTION!!!! Memory leak
   /* UnitObject* ent = nullptr;
    auto beg = EntitiesObserver::GetBeginIter();
    auto end = EntitiesObserver::GetAfterEndIter();
    for (;beg != end;++beg) {
        ent = dynamic_cast<UnitObject*>(*beg);
        if (ent != nullptr) {
            new UnitColliderVisualizer(*ent);
            new EntityAARadVisualizer(*ent);
            new EntityAutoAggrRadVisualizer(*ent);
        }
    }*/
}
GameMode::~GameMode() {
    delete GameInterface;

    Engine::UnloadCallbacksModules();
    LevelBypassMapManager::Unload();
    WorldTransfObjsCatalog::Unload();
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
