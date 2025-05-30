
#include <OrdersExecutor.h>

using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

ExecutorActionsMediator::ExecutorActionsMediator(OrdersExecutor& Owner)
	:Owner(Owner){

}
ExecutorActionsMediator::~ExecutorActionsMediator() {

}

void ExecutorActionsMediator::AddAction(IEntityAction* action) {
	Owner.ActionsToExecute->push_front(action);
}
void ExecutorActionsMediator::SetQueue(list<IEntityAction*>& actions) {
	Owner.UnloadActionsToDo();
	Owner.ChangeActionsToDo(&actions);
}
void ExecutorActionsMediator::ResetCurrActions() {
	Owner.UnloadActionsToDo();
}