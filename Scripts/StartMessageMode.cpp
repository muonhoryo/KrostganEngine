
#include <EngineModes.h>
#include <SFML/System.hpp>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::UI;
using namespace sf;

StartMessageMode::StartMessageMode() : EngineMode(),
	Message(MessageText,25U),
	InputHandler(StartMsgInputHandler()){

	Vector2u screenSize = Engine::GetScreenSize();

	Rect bounds = Message.text.getGlobalBounds();
	Vector2f center = Vector2f(bounds.left + 0.5f * bounds.width, bounds.top + bounds.height * 0.5f);
	Message.text.setOrigin(center);
	Message.ScreenPosition = Vector2f(((float)screenSize.x) / 2, ((float)screenSize.y) / 2);
	Message.text.setFillColor(Color(255U, 255U, 255U, 255U));
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

				LoadMessage = new TextBlock("Loading...", 30U);

				Vector2u screenSize = Engine::GetScreenSize();

				Rect bounds = LoadMessage->text.getGlobalBounds();
				Vector2f center = Vector2f(bounds.left + 0.5f * bounds.width, bounds.top + bounds.height * 0.5f);
				LoadMessage->text.setOrigin(center);
				LoadMessage->ScreenPosition = Vector2f(((float)screenSize.x)*3 / 4, ((float)screenSize.y)*3 / 4);
				LoadMessage->text.setFillColor(Color(0U, 255U, 0U, 255U));

				HasPressed = true;

				break;
			}
		}
	}
}