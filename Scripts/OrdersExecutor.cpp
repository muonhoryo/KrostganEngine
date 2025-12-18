
#include <OrdersExecutor.h>
#include <Extensions.h>
#include <EntityOrders.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

OrdersExecutor::OrdersExecutor(EntityBattleStats& BattleStats, AutoAttackModule* AAModule, AutoAggressionModule* AutoAggrModule)
	:BattleStats(BattleStats),
	ActionsToExecute(new list<IEntityAction*>()),
	CurrentActionToExecute(nullptr),
	CurrentOrder(nullptr){

	SetAAModule(AAModule);
	SetAutoAggrModule(AutoAggrModule);
}
OrdersExecutor::~OrdersExecutor() {

	delete AAModule;
	delete AutoAggrModule;
	if(ActionsToExecute!=nullptr)
		delete ActionsToExecute;
}

bool OrdersExecutor::GetAbilityToDoOrders() const {
	return AbleToDoOrders;
}
void OrdersExecutor::AllowOrdersExecution() {
	if (!AbleToDoOrders)
	{
		AbleToDoOrders = true;
	}
}
void OrdersExecutor::ProhibitOrdersExecution() {
	if (AbleToDoOrders) {

		AbleToDoOrders = false;
		AutoAggrModule->TurnOff();
		AAModule->SetAsTarget(nullptr);
		ResetOrdersQueue();
	}
}

bool OrdersExecutor::TryAddOrder(IEntityOrder& order, bool clearOrdQueue) {

	if (AbleToDoOrders && 
		CollectionsExts::IndexOf(GetAllowedOrdersCatalog(), order.GetOrderType()) != string::npos) { //Order's type is allowed

		EntityOrder_ObjectTarget* parOrd = dynamic_cast<EntityOrder_ObjectTarget*>(&order);
		if (parOrd != nullptr &&
			!parOrd->CanTargetItself()) {			//Order's target is object, but it cannot be executor

			const ITransformableObj* tar = parOrd->GetTarget();
			const OrdersExecutor* ordTar =dynamic_cast<const OrdersExecutor*>(tar);
			if (ordTar == this) {		//Order's target is executor

				delete &order;
				return false;
			}
		}

		if ((clearOrdQueue || order.IsCancelNextOrders()) && OrdersQueue.size() != 0)
		{
			ResetOrdersQueue();
		}
		OrdersQueue.push_back(&order);
		GetOrderEventHandler.Execute(order);
		return true;
	}
	delete &order;
	return false;
}
bool OrdersExecutor::TryInsertOrder(IEntityOrder& order, size_t insertPos, bool clearOrdQueue) {

	if (AbleToDoOrders &&
		CollectionsExts::IndexOf(GetAllowedOrdersCatalog(), order.GetOrderType()) != string::npos) { //Order's type is allowed

		EntityOrder_ObjectTarget* parOrd = dynamic_cast<EntityOrder_ObjectTarget*>(&order);
		if (parOrd != nullptr &&
			!parOrd->CanTargetItself()) {			//Order's target is object, but it cannot be executor

			const ITransformableObj* tar = parOrd->GetTarget();
			const OrdersExecutor* ordTar = dynamic_cast<const OrdersExecutor*>(tar);
			if (ordTar == this) {		//Order's target is executor

				delete& order;
				return false;
			}
		}

		if ((clearOrdQueue || order.IsCancelNextOrders()) && OrdersQueue.size() != 0)
		{
			ResetOrdersQueue();
		}

		CollectionsExts::Insert(OrdersQueue, &order, insertPos);
		GetOrderEventHandler.Execute(order);
		return true;
	}
	delete& order;
	return false;
}
void OrdersExecutor::ResetOrdersQueue() {
	if (!IsFirstOrderExecution()) {
		UnloadCurrentOrder();
	}
	OrdersQueue.clear();
	ResetOrderListEventHandler.Execute();
}
void OrdersExecutor::CancelOrder(size_t orderIndex) {
	if (orderIndex == 0) {
		UnloadCurrentOrder();
	}
	else {
		auto it = OrdersQueue.begin();
		auto end = OrdersQueue.end();
		for (size_t index = 0;index != orderIndex && it != end;++index) {
			++it;
		}

		if (it == end)
			throw exception("Index of order is out of range");

		auto order = *it;
		OrdersQueue.erase(it);
		ExecuteOrderEventHandler.Execute(*order);
		delete order;
	}
}

list<IEntityOrder*>::const_iterator OrdersExecutor::GetOrderQueueIter_Begin() const {
	return OrdersQueue.cbegin();
}
list<IEntityOrder*>::const_iterator OrdersExecutor::GetOrderQueueIter_AfterEnd() const {
	return OrdersQueue.cend();
}
EntityBattleStats& OrdersExecutor::GetBattleStats() const {
	return BattleStats;
}
AutoAttackModule& OrdersExecutor::GetAAModule() const {
	return *AAModule;
}
AutoAggressionModule& OrdersExecutor::GetAutoAggrModule() const {
	return *AutoAggrModule;
}

void OrdersExecutor::Update(CallbackRecArgs_Upd args) {
	HandleOrders(args);
	HandleActionsToDo(args);
}

void OrdersExecutor::HandleOrders(CallbackRecArgs_Upd& args) {
	if (IsFirstOrderExecution()) {
		if (OrdersQueue.size() != 0) {	//First order's execution
			FirstOrderExecution();
		}
	}
	else if (CurrentOrder->CheckExecCondition()) {
		UnloadCurrentOrder();
		if (OrdersQueue.size() != 0) {
			FirstOrderExecution();
		}
	}
}
void OrdersExecutor::HandleActionsToDo(CallbackRecArgs_Upd& args) {
	while (ActionsToExecute->size() != 0) {			//Is there any actions to do in queue

		if (CurrentActionToExecute == nullptr){		//Is current action is unloaded

			UpdateCurrActionToExec();				//Get next action to do
		}

		if (CurrentActionToExecute->CheckExecCondition()) {		//Is current action is complete
			
			//Check every action in queue until get action that needs to complete or queue is ended
			//Unload current action

			ActionsToExecute->pop_front();
			delete CurrentActionToExecute;

			if (ActionsToExecute->size() == 0) {		//Is every actions completed

				CurrentActionToExecute = nullptr;		//Empty field and set signal, that there is no actions to do
			}
			else {

				UpdateCurrActionToExec();				//Get next action to do
			}
		}
		else {

			//Execute current action
			CurrentActionToExecute->Execute();
			return;
		}
	}
	if (!IsFirstOrderExecution() && !CurrentOrder->CheckExecCondition()) {  //Order is still uncomplete, but previous actions is done

		UpdateActionsToDoFromOrder();		//Get actions from order
		UpdateCurrActionToExec();			//Get next action to do try to execute that
	}
}

void OrdersExecutor::FirstOrderExecution() {
	while (OrdersQueue.size() != 0) {
		CurrentOrder = OrdersQueue.front();
		if (CurrentOrder->CheckExecCondition()) {
			OrdersQueue.pop_front();
			ExecuteOrderEventHandler.Execute(*CurrentOrder);
			delete CurrentOrder;
		}
		else {
			UnloadActionsToDo();
			CurrentOrder->OnStartExecution();
			StartExecOrderEventHandler.Execute(*CurrentOrder);
			UpdateActionsToDoFromOrder();
			return;
		}
	}
	CurrentOrder = nullptr;
}
bool OrdersExecutor::IsFirstOrderExecution() {
	return CurrentOrder == nullptr;
}
void OrdersExecutor::UnloadCurrentOrder() {
	cout << "Order of type: " << (int)CurrentOrder->GetOrderType() << " is done" << endl;
	UnloadActionsToDo();

	OrdersQueue.pop_front();
	CurrentOrder->OnEndExecution();
	ExecuteOrderEventHandler.Execute(*CurrentOrder);
	delete CurrentOrder;
	CurrentOrder = nullptr;
}
void OrdersExecutor::UnloadActionsToDo() {
	if(ActionsToExecute!=nullptr)
		ActionsToExecute->clear();
	if (CurrentActionToExecute != nullptr) {
		delete CurrentActionToExecute;
	}
	CurrentActionToExecute = nullptr;
}
void OrdersExecutor::UpdateActionsToDoFromOrder() {
	ChangeActionsToDo(CurrentOrder->GetActions());
}
void OrdersExecutor::ChangeActionsToDo(list<IEntityAction*>* actions) {
	if (actions == nullptr) {
		if (ActionsToExecute == nullptr) {
			ActionsToExecute = new list<IEntityAction*>();
		}
	}
	else {
		if (ActionsToExecute != nullptr) {
			delete ActionsToExecute;
		}
		ActionsToExecute = actions;
	}
}
void OrdersExecutor::UpdateCurrActionToExec() {
	if (ActionsToExecute->size() > 0) {

		CurrentActionToExecute = ActionsToExecute->front();
		cout << "Execute action: " << typeid(*CurrentActionToExecute).name() << endl;
	}
}

ExecutorActionsMediator& OrdersExecutor::GetActionsMediator() {
	return *new ExecutorActionsMediator(*this);
}
void OrdersExecutor::SetAAModule(AutoAttackModule* aamodule) {
	if (AAModule != nullptr)
		delete AAModule;
	AAModule = aamodule;
}
void OrdersExecutor::SetAutoAggrModule(AutoAggressionModule* autoAggmodule) {
	if (AutoAggrModule != nullptr)
		delete AutoAggrModule;
	AutoAggrModule = autoAggmodule;
	if (AutoAggrModule != nullptr)
		AutoAggrModule->TurnOn();
}