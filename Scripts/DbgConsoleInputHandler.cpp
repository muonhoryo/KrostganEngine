
#include <DbgConsoleInputHandler.h>
#include <ConsoleCommsInterpretator.h>

using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::UI;

DbgConsoleInputHandler::DbgConsoleInputHandler()  {

}
DbgConsoleInputHandler::~DbgConsoleInputHandler() {

	TurnOffConsoleUI();
}

void DbgConsoleInputHandler::Update(const CallbackRecArgs_Upd& args) {

	for (auto& input : args.PlayerInput) {
		if (input.type == Event::KeyPressed) {

			if ((input.key.code >= Keyboard::Key::A && input.key.code <= Keyboard::Key::Num9) ||
				input.key.code==Keyboard::Key::Space ||
				input.key.code==Keyboard::Key::Add ||
				input.key.code == Keyboard::Key::Subtract ||
				input.key.code == Keyboard::Key::Hyphen||
				input.key.code == Keyboard::Key::Equal) {

				Input.push_back(FStreamExts::SFKeyToChar(input.key.code));
				DebugConsoleTextField->SetString(Input);
			}
			else if (input.key.code == Keyboard::Key::Enter) {

				ConsoleCommsInterpretator::ExecuteCommand(Input);
				delete this;
			}
			else if (input.key.code == Keyboard::Key::BackSpace &&
					Input.size()>0) {

				Input.pop_back();
				DebugConsoleTextField->SetString(Input);
			}
			else if (/*input.key.code == Keyboard::Key::Tilde ||*/
				input.key.code == Keyboard::Key::Escape) {

				delete this;
			}
		}
	}
}

void DbgConsoleInputHandler::StartHandling_Action() {

	TurnOnConsoleUI();
}
void DbgConsoleInputHandler::AbortHandling_Action() {

	TurnOffConsoleUI();
}

void DbgConsoleInputHandler::TurnOnConsoleUI() {

	DebugConsoleUI = UserInterfaceManager::GetRoot().GetUIElementByName(DBG_CONSOLE_UI_NAME);
	IsConsoleActive = true;

	if (DebugConsoleUI != nullptr) {

		DebugConsoleTextField = dynamic_cast<UIText*>(DebugConsoleUI->GetUIElementByName(DBG_CONSOLE_TEXTFIELD_NAME));

		if (DebugConsoleTextField != nullptr) {
			DebugConsoleUI->SetActivity(true);
			DebugConsoleTextField->SetActivity(true);
			Input = "";
			DebugConsoleTextField->SetString(Input);
		}
		else {
			DebugConsoleUI = nullptr;
		}
	}
}
void DbgConsoleInputHandler::TurnOffConsoleUI() {
	IsConsoleActive = false;
	if (DebugConsoleUI != nullptr) {
		DebugConsoleUI->SetActivity(false);
		DebugConsoleTextField->SetActivity(false);
		DebugConsoleTextField->SetString("");
		DebugConsoleUI = nullptr;
		DebugConsoleTextField = nullptr;
	}
}