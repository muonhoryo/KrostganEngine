
#include <EngineModes.h>
#include <Engine.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;


GameMode::GameMode() :EngineMode() {
    Window = &Engine::GetRenderWindow();
    BaseInputHandl = new BaseInputHandler();
    GroupSelectionHandl = new GroupSelectionHandler();
    OrdersInteraction = new OrdersSystemInteraction();
    GroupSelectSystem = &GroupSelectionSystem::GetInstance();
}
GameMode::~GameMode() {
	delete BaseInputHandl;
    delete GroupSelectionHandl;
    delete OrdersInteraction;
    delete GroupSelectSystem;
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetRenderModule().Execute();
}
