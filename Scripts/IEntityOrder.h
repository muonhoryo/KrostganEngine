#pragma once

#include <list>
#include <IEntityAction.h>
#include <EntityOrderType.h>

using namespace std;

namespace KrostganEngine::EntitiesControl {
	 class IEntityOrder {
	 public:
		 virtual ~IEntityOrder(){}

		virtual bool CheckExecCondition()=0;
		virtual list<IEntityAction*>* GetActions()=0;
		virtual void OnStartExecution() = 0;
		virtual void OnEndExecution() = 0;
		virtual EntityOrderType GetOrderType() = 0;

		virtual bool IsCancelNextOrders() { return false; }

	 protected:
		 IEntityOrder(){}
	};
}