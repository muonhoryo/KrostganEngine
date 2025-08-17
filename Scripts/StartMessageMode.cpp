
#include <EngineModes.h>
#include <SFML/System.hpp>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;
using namespace sf;

StartMessageMode::StartMessageMode() : EngineMode(),
	Message(
		nullptr,
		MessageText,
		25u,
		UserInterfaceManager::GetRoot().GetAnchoredGlobalPos(MESSAGE_ANCHOR),
		1,
		//Vector2f(0, 0)),
		Vector2f(MESSAGE_ANCHOR)),
	InputHandler(StartMsgInputHandler()){

	Message.SetColor(Color(255U, 255U, 255U, 255U));
}

void StartMessageMode::ExecuteCycle() {

    Engine::GetUpdateModule().Execute();
    Engine::GetRenderModule().Execute();
}

void StartMessageMode::StartMsgInputHandler::Update(CallbackRecArgs_Upd args) {

	if (HasPressed) {

		Engine::ReqToSetMode_LevelDeser();
	}
	else {
		for (auto& input : args.PlayerInput) {

			if (input.type == Event::KeyPressed &&
				input.key.code == Keyboard::Enter) {

				LoadMessage = new UIText(
					nullptr,
					"Loading...",
					30u,
					UserInterfaceManager::GetRoot().GetAnchoredGlobalPos(LOAD_MESSAGE_ANCHOR),
					1,
					Vector2f(LOAD_MESSAGE_ANCHOR));
				LoadMessage->SetColor(Color(0U, 255U, 0U, 255U));

				HasPressed = true;

				break;
			}
		}
	}
}