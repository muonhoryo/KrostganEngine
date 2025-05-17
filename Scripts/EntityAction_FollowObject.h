#pragma once

#include <EntityAction_MoveTo.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_FollowObject :public EntityAction_MoveTo {
	public:
		EntityAction_FollowObject(OrdersExecutor& Owner,TransformableObj& OwnerTransform, const TransformableObj& Target,const float DistToFoll);

		bool CheckExecCondition() override;
		void Execute() override;

		const TransformableObj& Target;
		const float DistToFoll;
	};
}