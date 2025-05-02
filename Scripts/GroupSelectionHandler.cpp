
#include <GroupSelectionHandler.h>
#include <ICallbackRec_Upd.h>
#include <SFML/System.hpp>
#include <EngineCore.h>
#include <Extensions.h>
#include <iostream>
#include <CoreEntitiesControl.h>
#include <CoreUIUX.h>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

GroupSelectionHandler::GroupSelectionHandler() {
	IsInSelProcess = false;
	SelectionUIQuad = nullptr;
}
GroupSelectionHandler::~GroupSelectionHandler() {

}

void GroupSelectionHandler::SelectionStartCheck(const Event& ev) {
	if (ev.type == Event::MouseButtonPressed &&
		ev.mouseButton.button == Mouse::Button::Left) {
		IsInSelProcess = true;
		SelectionStart = Vector2f((float)ev.mouseButton.x, (float)ev.mouseButton.y);
		SelectionStart = Engine::ScreenPosToGlobalCoord(SelectionStart);
		SelectionUIQuad = new GroupSelectionQuad(SelectionStart, SelectionStart);
		cout << "Start group selection: " + VectExts::ToString(SelectionStart)<< endl;
	}
}
void GroupSelectionHandler::SelectionEndCheck(const Event& ev) {
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
		delete SelectionUIQuad;
		SelectionUIQuad = nullptr;
		cout << "End group selection: " + VectExts::ToString(SelectionEnd) << endl;
		auto units = Engine::GetPhysicsEngine().OverlapAABB_All(minPos, maxPos, SELECTION_LAYER);
		forward_list<ISelectableEntity*> selecUnits = forward_list<ISelectableEntity*>();
		ISelectableEntity* ref = nullptr;
		for (auto un : units) {
			ref = dynamic_cast<ISelectableEntity*>(un);
			if(ref!=nullptr){
				selecUnits.push_front(ref);
			}
		}
		cout << "Selected objects count: "<< units.size() << endl;
		if (units.size() > 0) {
			GroupSelectionSystem::Clear();
			GroupSelectionSystem::AddRange(selecUnits.begin(),selecUnits.cend());
		}
		IsInSelProcess = false;
	}
	else{
		SelectionEnd = GetCursorGlobalPos();
		SelectionUIQuad->SetEndCorner(SelectionEnd);
	}
}
Vector2f GroupSelectionHandler::GetCursorGlobalPos() {
	Vector2f globalPos = Engine::GetCursorClampedPos();
	globalPos = Engine::ScreenPosToGlobalCoord(globalPos);
	return globalPos;
}

void GroupSelectionHandler::Update(CallbackRecArgs_Upd args) {
	for (auto &ev : args.PlayerInput) {
		if (IsInSelProcess) {
			SelectionEndCheck(ev);
		}
		else {
			SelectionStartCheck(ev);
		}
	}
}

const PhysicsLayer GroupSelectionHandler::SELECTION_LAYER = PhysicsLayer(((int)PhysicsLayer::Buildings)&((int)PhysicsLayer::Units));