
#include <EntitiesCtrlInputHandler.h>
#include <EntitiesCtrlInputModes.h>
#include <GroupSelectionSystem.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;

EntitiesCtrlInputHandler::EntitiesCtrlInputHandler():EntitiesCtrlInputHandler(new EntCtrlMode_Base(*this)) {}
EntitiesCtrlInputHandler::EntitiesCtrlInputHandler(EntitiesCtrlInputMode* mode)
	:CurrMode(mode)
{}
EntitiesCtrlInputHandler::~EntitiesCtrlInputHandler(){

}

void EntitiesCtrlInputHandler::SetNewMode(EntitiesCtrlInputMode& newMode) {
	if (&newMode!=nullptr) {
		delete CurrMode;
		CurrMode = &newMode;
	}
}
void EntitiesCtrlInputHandler::TurnOn() {

	if (!IsActive) {
		
		IsActive = true;
	}
}
void EntitiesCtrlInputHandler::TurnOff() {

	if (IsActive) {

		SetNewMode(*new EntCtrlMode_Base(*this));
		GroupSelectionSystem::Clear();
		IsActive = false;
	}
}

//bool EntitiesCtrlInputHandler::GetShiftPresState() {
//	return IsShiftPressed;
//}
//
//bool EntitiesCtrlInputHandler::HandleShiftInput(const Event& ev) {
//	
//	if (IsShiftPressed) {
//		if (ev.type == Event::KeyReleased && !ev.key.shift) {
//			IsShiftPressed = false;
//			return true;
//		}
//	}
//	else {
//		if (ev.type == Event::KeyPressed && ev.key.shift) {
//			IsShiftPressed = true;
//			return true;
//		}
//	}
//	return false;
//}

void EntitiesCtrlInputHandler::Update(const CallbackRecArgs_Upd& args) {

	if (IsActive) {
		CallbackRecArgs_Upd argCp = args;
		CurrMode->HandleInput(argCp);
	}
}