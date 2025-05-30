
#include <EntitiesCtrlInputModes.h>
#include <iostream>

#include <Engine.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::PlayerControl;

EntCtrlMode_Base::EntCtrlMode_Base(EntitiesCtrlInputHandler& Owner)
	:EntitiesCtrlInputMode(Owner){
	cout << "Turn input handling mode to Base"<<endl;
}

void EntCtrlMode_Base::HandleInput(CallbackRecArgs_Upd& args) {
	for (auto& input : args.PlayerInput) {
		if (input.type == Event::MouseButtonPressed) {
			if (input.key.code == Mouse::Right) {
				IAttackableObj* target=nullptr;
				Vector2f pos = GetPosByCursor();
				if (TryGetTargetByTypeAtPos(pos, target)) {
					IFractionMember* fracMember = dynamic_cast<IFractionMember*>(target);
					Relation rel = fracMember != nullptr ? FractionsSystem::GetRelation(Fraction::Player, fracMember->GetFraction()) : Relation::Neutral;
					if (rel == Relation::Enemy)
						GiveOrderToSelected_AttackTarget(*target);
					else
						GiveOrderToSelected_MoveToPoint(pos);
				}
				else {
					GiveOrderToSelected_MoveToPoint(pos);
				}
			}
			else if(input.mouseButton.button == Mouse::Button::Left) {
				Vector2f mousePos= Vector2f((float)input.mouseButton.x, (float)input.mouseButton.y);
				Owner.SetNewMode(*new EntCtrlMode_GroupSelect(Owner,mousePos));
				return;
			}
		}
		else if (input.type == Event::KeyPressed) {
			
			switch (input.key.code)
			{
			case Keyboard::A:
			{
				Owner.SetNewMode(*new EntCtrlMode_AttackOrder(Owner));
				cout << "Handle target of attack order" << endl;
				break;
			}
			case Keyboard::I:
			{
				GiveOrderToSelected_Idle();
				break;
			}
			case Keyboard::C:
			{
				GiveOrderToSelected_Cancel();
				break;
			}
			case Keyboard::H:
			{
				GiveOrderToSelected_HoldPosition();
				break;
			}
			default:
				break;
			}
		}
	}
}