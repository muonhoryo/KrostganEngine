
#include <EntitiesCtrlInputModes.h>
#include <iostream>
#include <GroupSelectionSystem.h>
#include <DBG_DivineCommander.h>

#include <Engine.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Debug;

EntCtrlMode_Base::EntCtrlMode_Base(EntitiesCtrlInputHandler& Owner)
	:EntitiesCtrlInputMode(Owner){
	cout << "Turn input handling mode to Base"<<endl;
}

bool EntCtrlMode_Base::AbleToGiveOrders() {
	return DBG_DivineCommander::GetActivity() ||
		GroupSelectionSystem::GetToPlayertRelOfSelEntities() == Relation::Ally;
}

void EntCtrlMode_Base::HandleInput(CallbackRecArgs_Upd& args) {

	for (auto& input : args.PlayerInput) {
		/*if (Owner.HandleShiftInput(input))
			continue;*/

		if (input.type == Event::MouseButtonPressed) {

			//Attack, follow or move
			if (input.key.code == Mouse::Right) {

				if (!AbleToGiveOrders())
					continue;

				IAttackableObj* target=nullptr;
				Vector2f pos = GetPosByCursor();
				if (TryGetTargetByTypeAtPos(pos, target)) {
					IFractionMember* fracMember = dynamic_cast<IFractionMember*>(target);
					Relation rel = fracMember != nullptr ? FractionsSystem::GetRelation(Fraction::Player, fracMember->GetFraction()) : Relation::Neutral;
					if (rel == Relation::Enemy)
						GiveOrderToSelected_AttackTarget(*target,PlayerInputManager::GetBtnState_Shift());
					else
						GiveOrderToSelected_FollowObject(*target, PlayerInputManager::GetBtnState_Shift());
				}
				else {
					GiveOrderToSelected_MoveToPoint(pos, PlayerInputManager::GetBtnState_Shift());
				}
			}
			
			//Select units
			else if(input.mouseButton.button == Mouse::Button::Left) {

				Vector2f mousePos= Vector2f((float)input.mouseButton.x, (float)input.mouseButton.y);
				Owner.SetNewMode(*new EntCtrlMode_GroupSelect(Owner,mousePos));
				return;
			}
		}
		else {	//Give order

			if (!AbleToGiveOrders())
				continue;

			if (input.type == Event::KeyPressed) {

				switch (input.key.code)
				{
				case Keyboard::A:
				{
					Owner.SetNewMode(*new EntCtrlMode_AttackOrder(Owner));
					cout << "Handle target of attack order" << endl;
					return;
				}
				case Keyboard::I:
				{
					GiveOrderToSelected_Idle(PlayerInputManager::GetBtnState_Shift());
					break;
				}
				case Keyboard::C:
				{
					GiveOrderToSelected_Cancel();
					break;
				}
				case Keyboard::H:
				{
					GiveOrderToSelected_HoldPosition(PlayerInputManager::GetBtnState_Shift());
					break;
				}
				default:
					break;
				}
			}
		}
	}
}