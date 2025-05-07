
#include <Entity.h>
#include <EntityOrders.h>
#include <Extensions.h>
#include <string>
#include <ICallbackRec_Upd.h>
#include <EntityOrder_GlobalPosTarget.h>
#include <EntityOrder_ObjectTarget.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

bool Entity::TryAddOrder(IEntityOrder* order,bool clearOrdQueue) {
	if (CollectionsExts::IndexOf(GetAllowedOrdersCatalog(), order->GetOrderType()) != string::npos) { //Order's type is allowed

		EntityOrder_ObjectTarget* parOrd = dynamic_cast<EntityOrder_ObjectTarget*>(order);
		if (parOrd != nullptr&&
			!parOrd->CanTargetItself()) {			//Order's target is object, but it cannot be executor
			const TransformableObj* ordTar = &parOrd->GetTarget();
			if (ordTar == this) {		//Order's target is executor
				return false;
			}
		}

		if (clearOrdQueue && OrdersQueue.size() != 0)
		{
			ResetOrdersQueue();
		}
		OrdersQueue.push_back(order);
		auto parOrder = dynamic_cast<EntityOrder_GlobalPosTarget*>(order);
		if (parOrder != nullptr) {
			OrdersTargetsVisualizer->AddPoint(parOrder->TargetGlobalPos);
		}
		GetOrderEventHandler.Execute(order);
		return true;
	}
	return false;
}
void Entity::ResetOrdersQueue() {
	if (!IsFirstOrderExecution()) {
		UnloadCurrentOrder();
	}
	OrdersQueue.clear();
	OrdersTargetsVisualizer->ReduceSize(1);
	ResetOrderListEventHandler.Execute();
}

list<IEntityOrder*>::const_iterator Entity::GetOrderQueueIter_Begin() const{
	return OrdersQueue.cbegin();
}

list<IEntityOrder*>::const_iterator Entity::GetOrderQueueIter_AfterEnd()const {
	return OrdersQueue.cend();
}

void Entity::Update(CallbackRecArgs_Upd args) {
	HandleOrders(args);
	HandleActionsToDo(args);
}

void Entity::HandleOrders(CallbackRecArgs_Upd& args) {
	if (IsFirstOrderExecution()) {
		if (OrdersQueue.size() != 0) {	//First order's execution
			FirstOrderExecution();
		}
	}
	else if(CurrentOrder->CheckExecCondition()) {
		UnloadCurrentOrder();
		if (OrdersQueue.size() != 0) {
			FirstOrderExecution();
		}
	}
}
void Entity::FirstOrderExecution() {
	while (OrdersQueue.size() != 0) {
		CurrentOrder = OrdersQueue.front();
		if (CurrentOrder->CheckExecCondition()) {
			OrdersQueue.pop_front();
		}
		else {
			CurrentOrder->OnStartExecution();
			UpdateActionsToDoFromOrder();
			return;
		}
	}
}
bool Entity::IsFirstOrderExecution() {
	return CurrentOrder == nullptr;
}
void Entity::UnloadCurrentOrder() {
	cout << "Order of type: " << (int)CurrentOrder->GetOrderType() << " is done" << endl;
	ActionsToExecute->clear();
	if (CurrentActionToExecute != nullptr) {
		delete CurrentActionToExecute;
	}
	CurrentActionToExecute = nullptr;

	OrdersQueue.pop_front();
	CurrentOrder->OnEndExecution();
	auto parOrder = dynamic_cast<EntityOrder_GlobalPosTarget*>(CurrentOrder);
	if (parOrder != nullptr)
		OrdersTargetsVisualizer->RemovePointAt(1);
	ExecuteOrderEventHandler.Execute(CurrentOrder);
	delete CurrentOrder;
	CurrentOrder = nullptr;
}

void Entity::HandleActionsToDo(CallbackRecArgs_Upd& args) {
	while (ActionsToExecute->size() != 0) {
		if (CurrentActionToExecute == nullptr) {
			CurrentActionToExecute = ActionsToExecute->front();
			cout << "Execute action: " << typeid(*CurrentActionToExecute).name() << endl;
		}
		
		if (CurrentActionToExecute->CheckExecCondition()) {
			ActionsToExecute->pop_front();
			delete CurrentActionToExecute;
			if (ActionsToExecute->size() == 0) {
				CurrentActionToExecute = nullptr;
			}
			else {
				CurrentActionToExecute = ActionsToExecute->front();
				cout << "Execute action: " << typeid(*CurrentActionToExecute).name() << endl;
			}
		}
		else {
			CurrentActionToExecute->Execute();
			return;
		}
	}
	if (!IsFirstOrderExecution() && !CurrentOrder->CheckExecCondition()) {  //Order is still uncomplete, but previous actions is done
		UpdateActionsToDoFromOrder();
		CurrentActionToExecute = ActionsToExecute->front();
		cout << "Execute action: " << typeid(*CurrentActionToExecute).name() << endl;
	}
}
void Entity::UpdateActionsToDoFromOrder() {
	if (ActionsToExecute != nullptr) {
		delete ActionsToExecute;
	}
	ActionsToExecute = &CurrentOrder->GetActions();
}