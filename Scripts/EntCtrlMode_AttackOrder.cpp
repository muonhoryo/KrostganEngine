
#include <EntitiesCtrlInputModes.h>
#include <iostream>
#include <Engine.h>
#include <_ExternalData.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::PlayerControl;

EntCtrlMode_AttackOrder::EntCtrlMode_AttackOrder(EntitiesCtrlInputHandler& Owner) :EntitiesCtrlInputMode(Owner){

	Engine::GetCursorManager().SetAttackOrderSprite();
	cout << "Turn input handling mode to Attack order" << endl;
	PlayerInputManager::SetBtnState_Escape(true);
}
EntCtrlMode_AttackOrder::~EntCtrlMode_AttackOrder() {
	Engine::GetCursorManager().SetDefaultSprite();
	PlayerInputManager::SetBtnState_Escape(false);
}

void EntCtrlMode_AttackOrder::HandleInput(CallbackRecArgs_Upd& args) {
	for (auto& input : args.PlayerInput) {
		if (input.type == Event::MouseButtonPressed) {
			if (input.key.code == Mouse::Left) {
				IAttackableObj* target = nullptr;
				Vector2f pos = GetPosByCursor();
				if (TryGetTargetByTypeAtPos(pos, target)) {

					GiveOrderToSelected_AttackTarget(*target, PlayerInputManager::GetBtnState_Shift());
				}
				else {
					GiveOrderToSelected_AttackArea(pos, PlayerInputManager::GetBtnState_Shift());
				}
			}
			Owner.SetNewMode(*new EntCtrlMode_Base(Owner));
			return;
		}
		else if (input.type == Event::KeyPressed &&
					(input.key.code==Keyboard::Escape||
					input.key.code==Engine::GetPlayerCtrlSettings().Btn_Order_Attack)) {

			Owner.SetNewMode(*new EntCtrlMode_Base(Owner));
			return;
		}
	}
}