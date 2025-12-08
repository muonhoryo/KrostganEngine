
#include <EntitiesCtrlInputModes.h>
#include <Engine.h>
#include <Extensions.h>

using namespace KrostganEngine;
using namespace KrostganEngine::PlayerControl;

EntCtrlMode_GroupSelect::EntCtrlMode_GroupSelect(EntitiesCtrlInputHandler& Owner,Vector2f startMousePos)
	:EntitiesCtrlInputMode(Owner),
	SelectionUIQuad(nullptr){

	SelectionStart = Engine::ScreenPosToGlobalCoord(startMousePos);
	SelectionUIQuad = new GroupSelectionQuad(SelectionStart, SelectionStart);
}
EntCtrlMode_GroupSelect::~EntCtrlMode_GroupSelect(){
	delete SelectionUIQuad;
}

void EntCtrlMode_GroupSelect::HandleInput(CallbackRecArgs_Upd& args) {
	for (auto& ev : args.PlayerInput) {
		if (ev.type == Event::MouseButtonReleased &&
			ev.mouseButton.button == Mouse::Button::Left) {

			SelectionEnd = GetCursorGlobalPos();
			Vector2f minPos;
			Vector2f maxPos;
			if (SelectionStart.x < SelectionEnd.x) {
				minPos.x = SelectionStart.x;
				maxPos.x = SelectionEnd.x;
			}
			else {
				minPos.x = SelectionEnd.x;
				maxPos.x = SelectionStart.x;
			}
			if (SelectionStart.y < SelectionEnd.y) {
				minPos.y = SelectionStart.y;
				maxPos.y = SelectionEnd.y;
			}
			else {
				minPos.y = SelectionEnd.y;
				maxPos.y = SelectionStart.y;
			}
			auto units = Engine::GetPhysicsEngine().OverlapAABB_All(minPos, maxPos, SELECTION_LAYER);
			forward_list<ISelectableEntity*> selecUnits = forward_list<ISelectableEntity*>();
			ISelectableEntity* ref = nullptr;
			for (auto un : units) {
				ref = dynamic_cast<ISelectableEntity*>(un);
				if (ref != nullptr) {
					selecUnits.push_front(ref);
				}
			}
			if (units.size() > 0) {

				if (PlayerInputManager::GetBtnState_Ctrl()) {

					GroupSelectionSystem::RemoveRange(selecUnits.cbegin(), selecUnits.cend());
				}
				else {

					if (!PlayerInputManager::GetBtnState_Shift())
						GroupSelectionSystem::Clear();
					GroupSelectionSystem::AddRange(selecUnits.cbegin(), selecUnits.cend());
				}
			}

			Owner.SetNewMode(*new EntCtrlMode_Base(Owner));
			return;
		}
		else {
			SelectionEnd = GetCursorGlobalPos();
			SelectionUIQuad->SetEndCorner(SelectionEnd);
		}
	}
}

Vector2f EntCtrlMode_GroupSelect::GetCursorGlobalPos() {
	Vector2f globalPos = Engine::GetCursorClampedPos();
	globalPos = Engine::ScreenPosToGlobalCoord(globalPos);
	return globalPos;
}

const PhysicsLayer EntCtrlMode_GroupSelect::SELECTION_LAYER= PhysicsLayer(((int)PhysicsLayer::Buildings) | ((int)PhysicsLayer::Units));