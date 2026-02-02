
#include <SFML/System.hpp>
#include <Engine.h>
#include <_ExternalData.h>
#include <VectExts.h>
#include <_InputHandlers.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;
using namespace sf;

MainMenuMode::MainMenuMode() : EngineMode(){

	UserInterfaceLoader::Load_MainMenu();
	new MainMenuTransitionHandler();
	new BaseAppInputHandler();
}
MainMenuMode::~MainMenuMode() {

	Engine::UnloadCallbacksModules();
	PlayerInputManager::Clear();
}

void MainMenuMode::ExecuteCycle() {

	Engine::GetUpdateModule().Execute();
	Engine::GetLateUpdModule().Execute();
	Engine::GetRenderModule().Execute();
}