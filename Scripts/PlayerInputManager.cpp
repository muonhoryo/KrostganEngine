
#include <PlayerInputManager.h>
#include <Engine.h>

using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine;

bool PlayerInputManager::GetBtnState_Escape() {

	if (FreeBtn_Escape) {

		float time = ReservBtnDelay_Escape.getElapsedTime().asSeconds();
		float reqTime = Engine::GetGlobalConsts().EscapeBtn_PressDelay;
		if (time >= reqTime) {
			IsReservedBtn_Escape = false;
			FreeBtn_Escape = false;
			return false;
		}
		else
			return true;
	}
	else
		return IsReservedBtn_Escape;
}
void PlayerInputManager::SetBtnState_Escape(bool newState) {
	if (newState != IsReservedBtn_Escape) {

		if (!newState) {
			ReservBtnDelay_Escape.restart();
			FreeBtn_Escape = true;
		}
		else {
			IsReservedBtn_Escape = true;
		}
	}
}