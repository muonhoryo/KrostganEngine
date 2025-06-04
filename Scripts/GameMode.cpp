
#include <EngineModes.h>
#include <Engine.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;


GameMode::GameMode() :EngineMode() {
    Window = &Engine::GetRenderWindow();
    BaseInputHandl = new BaseInputHandler();
    EntitiesCtrlHandler = new EntitiesCtrlInputHandler();
    GameInterface = new GameUI();
}
GameMode::~GameMode() {
	delete BaseInputHandl;
    delete EntitiesCtrlHandler;
    delete GameInterface;
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetLateUpdModule().Execute();
    Engine::GetRenderModule().Execute();
}
