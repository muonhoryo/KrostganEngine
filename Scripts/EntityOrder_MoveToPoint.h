#pragma once

#include <IEntityOrder.h>
#include <SFML/System.hpp>
#include <Entity.h>
#include <EntityOrder_GlobalPosTarget.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_MoveToPoint :public IEntityOrder,public EntityOrder_GlobalPosTarget {
	public:
		EntityOrder_MoveToPoint(Entity& Owner,Vector2f TargetGlobalCoord);

		bool CheckExecCondition() override;
		list<IEntityAction*>& GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		Entity& Owner;
	};
}