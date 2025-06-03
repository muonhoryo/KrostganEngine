
#include <BaseInputHandler.h>
#include <ConsoleCommsInterpretator.h>
#include <EngineCore.h>
#include <Extensions.h>

using namespace KrostganEngine;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;


BaseInputHandler::BaseInputHandler() {
}
void BaseInputHandler::Update(CallbackRecArgs_Upd args) {

	for (auto &input : args.PlayerInput) {

		if (input.type == Event::KeyPressed) {

			if (input.key.code == Keyboard::Tilde) { //Open console

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

	//Check camera movement

	if (Engine::IsMouseOnScreen() && Engine::HasWindowFocus())
	{
		Vector2f curPos = Engine::GetCursorClampedPos();
		float trigger = Engine::GetGlobalConsts().CameraMovTriggerArea;
		Vector2u scrSize = Engine::GetScreenSize();
		Vector2i cameraMov = Vector2i(
			curPos.x < trigger ? -1 : (float)scrSize.x - curPos.x < trigger ? 1 : 0,
			curPos.y < trigger ? -1 : (float)scrSize.y - curPos.y < trigger ? 1 : 0);

		if (cameraMov != VECTOR2_INT_ZERO) {

			float movStep = Engine::GetEngineConfig().Camera_MovSpeed;
			Vector2f movVect = Vector2f(cameraMov.x * movStep, cameraMov.y * movStep);
			Engine::MoveCamera(movVect);
		}
	}
}