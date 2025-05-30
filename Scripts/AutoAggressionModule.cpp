
#include <OrdersExecutor.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

AutoAggressionModule::AutoAggressionModule(ExecutorActionsMediator& ActionMediator) : ICallbackRec_Upd(),
	ActionMediator(ActionMediator)
{
	IsActive = false;
	IsFollowTargets = true;
}
AutoAggressionModule::~AutoAggressionModule() {
	delete &ActionMediator;
}

void AutoAggressionModule::TurnOn() {
	if (!IsActive){
		TurnOnAction();
		cout << "Turn auto aggresion on"<<endl;
	}
}
void AutoAggressionModule::TurnOff() {
	if (IsActive) {
		TurnOffAction();
		cout << "Turn auto aggression off"<<endl;
	}
}
void AutoAggressionModule::TurnTargetFollowingOn() {
	if (!IsFollowTargets) {
		TurnTarFollOnAction();
	}
}
void AutoAggressionModule::TurnTargetFollowingOff() {
	if (IsFollowTargets) {
		TurnTarFollOffAction();
	}
}
void AutoAggressionModule::Restart() {
	TurnOff();
	TurnOnAction();
}

bool AutoAggressionModule::GetActiveState()const {
	return IsActive;
}
bool AutoAggressionModule::GetIsFollTarState()const {
	return IsFollowTargets;
}

void AutoAggressionModule::Update(CallbackRecArgs_Upd args) {
	if (IsActive) {
		UpdateAction(args);
	}
}


void AutoAggressionModule::TurnOnAction() {
	IsActive = true;
}
void AutoAggressionModule::TurnOffAction() {
	IsActive = false;
}
void AutoAggressionModule::TurnTarFollOnAction() {
	IsFollowTargets = true;
}
void AutoAggressionModule::TurnTarFollOffAction() {
	IsFollowTargets = false;
}