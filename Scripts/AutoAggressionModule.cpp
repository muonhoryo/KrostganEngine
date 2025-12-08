
#include <OrdersExecutor.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;

AutoAggressionModule::AutoAggressionModule(ExecutorActionsMediator& ActionMediator, ExecutedEvent<const IEntityOrder>& StartExecOrderEvent) : ICallbackRec_Upd(),
	ActionMediator(ActionMediator),
	StartExecOrderEvent(StartExecOrderEvent),
	StartExecOrderSubscr(*new OnStartOrderExecAction(*this))
{
	IsActive = false;
	IsFollowTargets = true;
	StartExecOrderEvent.Add(StartExecOrderSubscr);
}
AutoAggressionModule::~AutoAggressionModule() {
	delete &ActionMediator;
	delete &StartExecOrderSubscr;
}

void AutoAggressionModule::TurnOn() {
	if (!IsActive){
		TurnOnAction();
	}
}
void AutoAggressionModule::TurnOff() {
	if (IsActive) {
		TurnOffAction();
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

bool AutoAggressionModule::GetActivityState()const {
	return IsActive;
}
bool AutoAggressionModule::GetIsFollTarState()const {
	return IsFollowTargets;
}

void AutoAggressionModule::Update(CallbackRecArgs_Upd args) {
	if (GetActivityState()) {
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

AutoAggressionModule::OnStartOrderExecAction::OnStartOrderExecAction(AutoAggressionModule& Owner) 
	:Owner(Owner) {
}

void AutoAggressionModule::OnStartOrderExecAction::Execute(const IEntityOrder& ord) {

	if (Owner.GetActivityState())
		Owner.Restart();
}