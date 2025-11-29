
#include <EngineModes.h>
#include <SFML/System.hpp>
#include <Engine.h>
#include <ExternalData.h>
#include <VectExts.h>
#include <InputHandlers.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;
using namespace sf;

MainMenuMode::MainMenuMode() : EngineMode(){

	UserInterfaceLoader::Load_MainMenu();
	new MainMenuTransitionHandler();
}
MainMenuMode::~MainMenuMode() {

	PlayerInputManager::Clear();
}

void MainMenuMode::ExecuteCycle() {

	Engine::GetUpdateModule().Execute();
	Engine::GetRenderModule().Execute();
}