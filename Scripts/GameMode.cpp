
#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <PlayerControl.h>
#include <EntitiesControl.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;


GameMode::GameMode() :EngineMode() {
    Window = &Engine::GetRenderWindow();
    BaseInputHandl = new BaseInputHandler();
    GroupSelectionHandl = new GroupSelectionHandler();
    GroupSelectSystem = &GroupSelectionSystem::GetInstance();
}
GameMode::~GameMode() {
	delete BaseInputHandl;
    delete GroupSelectionHandl;
    delete GroupSelectSystem;
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetRenderModule().Execute();
}
