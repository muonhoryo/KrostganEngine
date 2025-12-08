
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
void EntitiesCtrlInputHandler::Update(const CallbackRecArgs_Upd& args) {

	if (IsActive) {
		CallbackRecArgs_Upd argCp = args;
		CurrMode->HandleInput(argCp);
	}
}