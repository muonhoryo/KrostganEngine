
#include <EntitiesCtrlInputModes.h>
#include <iostream>
#include <Engine.h>
#include <ExternalData.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::PlayerControl;

EntCtrlMode_AttackOrder::EntCtrlMode_AttackOrder(EntitiesCtrlInputHandler& Owner) :EntitiesCtrlInputMode(Owner){

	Engine::GetCursorManager().SetAttackOrderSprite();
	cout << "Turn input handling mode to Attack order" << endl;
}
EntCtrlMode_AttackOrder::~EntCtrlMode_AttackOrder() {
	Engine::GetCursorManager().SetDefaultSprite();
}

void EntCtrlMode_AttackOrder::HandleInput(CallbackRecArgs_Upd& args) {
	for (auto& input : args.PlayerInput) {
		if (input.type == Event::MouseButtonPressed) {
			if (input.key.code == Mouse::Left) {
				IAttackableObj* target = nullptr;
				Vector2f pos = GetPosByCursor();
				if (TryGetTargetByTypeAtPos(pos, target)) {

					GiveOrderToSelected_AttackTarget(*target, Owner.GetShiftPresState());
				}
				else {
					GiveOrderToSelected_AttackArea(pos, Owner.GetShiftPresState());
				}
			}
			Owner.SetNewMode(*new EntCtrlMode_Base(Owner));
			return;
		}
	}
}