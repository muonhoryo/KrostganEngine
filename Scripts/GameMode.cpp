
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
	if (!args.Window.isOpen())
		return;
	while (args.Window.pollEvent(args.UpdateEvent)) {
		if (args.UpdateEvent.type == Event::Closed)
		{
			args.Window.close();
			exit(1);
		}
		else if (args.UpdateEvent.type == Event::KeyPressed&&
			args.UpdateEvent.key.code==Keyboard::Tilde) {
			cout << "Enter command:";
			fflush(stdin);
			cin.clear();
			string input;
			getline(cin, input);
			if (input.size() > 0)
				ConsoleCommsInterpretator::ExecuteCommand(input);
			Engine::GetRenderWindow().requestFocus();
		}
		if (!args.Window.isOpen())
			return;
	}
}

GameMode::GameMode() :EngineMode() {
    InputHandler = new GameModeInputHandler();
    Window = &Engine::GetRenderWindow();
    Engine::GetUpdateModule().Add(InputHandler);
}
GameMode::~GameMode() {
    Engine::GetUpdateModule().Remove(InputHandler);
}
void GameMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetRenderModule().Execute();

}
