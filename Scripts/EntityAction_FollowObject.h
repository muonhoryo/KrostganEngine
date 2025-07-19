#pragma once

#include <EntityAction_MoveTo.h>
#include <watch_ptr.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_FollowObject :public EntityAction_MoveTo {
	public:
		EntityAction_FollowObject	
			(OrdersExecutor&							Owner,
			TransformableObj&							OwnerTransform, 
			watch_ptr_handler_wr_c<TransformableObj>	Target,
			const float									DistToFoll);
		~EntityAction_FollowObject();

		bool CheckExecCondition() override;
		void Execute() override;

		watch_ptr_handler_wr_c<TransformableObj>	Target;
		const float									DistToFoll;
	};
}