
#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <LevelLoading.h>
#include<EngineCallbacks.h>
#include <ICallbackRec_Upd.h>
#include <iostream>
#include <Debug.h>

using namespace KrostganEngine::Core;
using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace std;
using namespace KrostganEngine::Debug;

GameMode::GameModeInputHandler::GameModeInputHandler() {
}
void GameMode::GameModeInputHandler::Update(CallbackRecArgs_Upd args) {

	for (auto input :args.PlayerInput) {
		if (input.type == Event::KeyPressed &&
			input.key.code == Keyboard::Tilde) {
			cout << "Enter command:";
			fflush(stdin);
			cin.clear();
			string input;
			getline(cin, input);
			if (input.size() > 0)
				ConsoleCommsInterpretator::ExecuteCommand(input);
			Engine::GetRenderWindow().requestFocus();
		}
	}
}

GameMode::GameMode() :EngineMode() {
    InputHandler = new GameModeInputHandler();
    Window = &Engine::GetRenderWindow();
}
GameMode::~GameMode() {
	delete InputHandler;
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetRenderModule().Execute();

}
