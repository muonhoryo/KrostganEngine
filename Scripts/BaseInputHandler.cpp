
#include <BaseInputHandler.h>
#include <ConsoleCommsInterpretator.h>
#include <EngineCore.h>

using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;


BaseInputHandler::BaseInputHandler() {
}
void BaseInputHandler::Update(CallbackRecArgs_Upd args) {

	for (auto &input : args.PlayerInput) {
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