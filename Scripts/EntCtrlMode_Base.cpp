
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
				GiveOrderToSelected_MoveToPoint();
			}
			else if(input.mouseButton.button == Mouse::Button::Left) {
				Vector2f mousePos= Vector2f((float)input.mouseButton.x, (float)input.mouseButton.y);
				Owner.SetNewMode(*new EntCtrlMode_GroupSelect(Owner,mousePos));
				return;
			}
		}
		else if (input.type == Event::KeyPressed) {
			if (input.key.code == Keyboard::A) {
				Owner.SetNewMode(*new EntCtrlMode_AttackOrder(Owner));
				cout << "Handle target of attack order" << endl;
				return;
			}
		}
	}
}