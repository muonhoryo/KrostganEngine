#pragma once

#include <EntityAction_MoveTo.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_MoveToPoint :public EntityAction_MoveTo{
	public:
		EntityAction_MoveToPoint(OrdersExecutor& Owner,WorldTransfObj& OwnerTransform,Vector2f TargetGlobalCoord);

		bool CheckExecCondition() override;
		void Execute() override;

		const Vector2f TargetGlobalCoord;
	};
}