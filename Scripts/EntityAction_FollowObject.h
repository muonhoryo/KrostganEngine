#pragma once

#include <EntityAction_MoveTo.h>
#include <Entity.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_FollowObject :public EntityAction_MoveTo {
	public:
		EntityAction_FollowObject(Entity& Owner, const TransformableObj& Target,const float DistToFoll);

		bool CheckExecCondition() override;
		void Execute() override;

		const TransformableObj& Target;
		const float DistToFoll;
	};
}