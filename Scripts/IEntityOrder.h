#pragma once

#include <list>
#include <IEntityAction.h>
#include <EntityOrderType.h>

using namespace std;

namespace KrostganEngine::EntitiesControl {
	 class IEntityOrder {
	 public:
		virtual bool CheckExecCondition()=0;
		virtual list<IEntityAction*>& GetActions()=0;
		virtual void OnStartExecution() = 0;
		virtual void OnEndExecution() = 0;
		virtual EntityOrderType GetOrderType() = 0;

	 protected:
		 IEntityOrder() :IsDataInv(false){}

		 bool IsDataInv;
	};
}