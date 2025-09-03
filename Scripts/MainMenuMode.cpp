
#include <EngineModes.h>
#include <SFML/System.hpp>
#include <Engine.h>
#include <ExternalData.h>
#include <VectExts.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;
using namespace sf;

MainMenuMode::MainMenuMode() : EngineMode(){

	UserInterfaceLoader::Load_MainMenu();
}

void MainMenuMode::ExecuteCycle() {

	Engine::GetUpdateModule().Execute();
	Engine::GetRenderModule().Execute();
}

void MainMenuMode::MainMenuInputHandler::Update(CallbackRecArgs_Upd args) {

	if (HasPressed) {

		Engine::ReqToSetMode_LevelDeser();
	}
	else {
		for (auto& input : args.PlayerInput) {

			if (input.type == Event::KeyPressed &&
				input.key.code == Keyboard::Enter) {

				UserInterfaceLoader::Load_LevelDeserialization();

				HasPressed = true;

				break;
			}
		}
	}
}