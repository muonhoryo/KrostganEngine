
#include <EntitiesCtrlInputHandler.h>
#include <EntitiesCtrlInputModes.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::PlayerControl;

EntitiesCtrlInputHandler::EntitiesCtrlInputHandler():EntitiesCtrlInputHandler(new EntCtrlMode_Base(*this)){}
EntitiesCtrlInputHandler::EntitiesCtrlInputHandler(EntitiesCtrlInputMode* CurrMode) 
	:CurrMode(CurrMode){

}

void EntitiesCtrlInputHandler::SetNewMode(EntitiesCtrlInputMode& newMode) {
	if (&newMode!=nullptr) {
		delete CurrMode;
		CurrMode = &newMode;
	}
}

bool EntitiesCtrlInputHandler::GetShiftPresState() {
	return IsShiftPressed;
}

bool EntitiesCtrlInputHandler::HandleShiftInput(const Event& ev) {
	
	if (IsShiftPressed) {
		if (ev.type == Event::KeyReleased && !ev.key.shift) {
			IsShiftPressed = false;
			return true;
		}
	}
	else {
		if (ev.type == Event::KeyPressed && ev.key.shift) {
			IsShiftPressed = true;
			return true;
		}
	}
	return false;
}

void EntitiesCtrlInputHandler::Update(CallbackRecArgs_Upd args) {
	CurrMode->HandleInput(args);
}