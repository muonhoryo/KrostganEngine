
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
}

bool EntCtrlMode_Base::AbleToGiveOrders() {
	return DBG_DivineCommander::GetActivity() ||
		GroupSelectionSystem::GetToPlayertRelOfSelEntities() == Relation::Ally;
}

void EntCtrlMode_Base::HandleInput(CallbackRecArgs_Upd& args) {

	for (auto& input : args.PlayerInput) {

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
		else if (input.type == Event::KeyPressed) {

			if (AbleToGiveOrders()) {

				//Give order
				switch (input.key.code)
				{
				case Keyboard::A:
				{
					Owner.SetNewMode(*new EntCtrlMode_AttackOrder(Owner));
					return;
				}
				case Keyboard::I:
				{
					GiveOrderToSelected_Idle(PlayerInputManager::GetBtnState_Shift());
					continue;
				}
				case Keyboard::C:
				{
					GiveOrderToSelected_Cancel();
					continue;
				}
				case Keyboard::H:
				{
					GiveOrderToSelected_HoldPosition(PlayerInputManager::GetBtnState_Shift());
					continue;
				}
				case Keyboard::Num1:
				{
					GiveOrderToChoosen_UseAbility(0);
				}
				default:
					break;
				}
			}

			switch (input.key.code) {
			case Keyboard::Tab:
			{
				GroupSelectionSystem::ChoiseNextEntsGroup();
				continue;
			}
			default:
				break;
			}
		}
	}
}