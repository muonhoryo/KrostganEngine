
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


bool AutoAggressionModule::GetActiveState() {
	return IsActive;
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