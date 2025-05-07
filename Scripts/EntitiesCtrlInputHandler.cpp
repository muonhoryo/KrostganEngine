
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

void EntitiesCtrlInputHandler::Update(CallbackRecArgs_Upd args) {
	CurrMode->HandleInput(args);
}