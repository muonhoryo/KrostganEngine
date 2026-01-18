#pragma once

#include <IEntityOrder.h>
#include <SFML/System.hpp>
#include <OrdersExecutor.h>
#include <Entity.h>
#include <EntityOrder_GlobalPosTarget.h>
#include <EntityOrder_ImmobilityChecking.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_MoveToPoint :public IEntityOrder,public EntityOrder_GlobalPosTarget, public virtual EntityOrder_ImmobilityChecking {
	public:
		EntityOrder_MoveToPoint(
			OrdersExecutor&		Owner,
			Vector2f			TargetGlobalCoord,
			float				ToTargetMinDistance = 0);

		bool CheckExecCondition() override;
		list<IEntityAction*>* GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		OrdersExecutor& Owner;
		float ToTargetMinDistance_Sqr;
	};
}