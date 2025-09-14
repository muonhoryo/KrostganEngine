
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
	cout << "Turn input handling mode to Group selection" << endl;
	cout << "Start group selection: " + to_string(SelectionStart) << endl;
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
			cout << "End group selection: " + to_string(SelectionEnd) << endl;
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
				if(!Owner.GetShiftPresState())
					GroupSelectionSystem::Clear();
				GroupSelectionSystem::AddRange(selecUnits.begin(), selecUnits.cend());
			}

			cout << "Selected objects count: " << units.size() << endl;
			auto beg = GroupSelectionSystem::GetEntitiesBegIter();
			auto end = GroupSelectionSystem::GetEntitiesEndIter();
			const CatalogObject* parObj = nullptr;
			for (;beg != end;++beg) {
				parObj = dynamic_cast<const CatalogObject*>((*beg)->GetPtr_t_c());
				if (parObj == nullptr)
					cout << "0:0\t";
				else
					cout << parObj->GetCatalogID() << ":" << (int)parObj->GetSubcatalogID()<<"\t";
			}
			cout << endl;

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