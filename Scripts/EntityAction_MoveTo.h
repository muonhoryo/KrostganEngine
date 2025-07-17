#pragma once

#include <IEntityAction.h>
#include <OrdersExecutor.h>
#include <SFML/System.hpp>
#include <TransformableObj.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_MoveTo:public IEntityAction {
	public:
		EntityAction_MoveTo(OrdersExecutor& Owner,TransformableObj& OwnerTransform);

	protected:
		float DistToTarget;
		OrdersExecutor& Owner;
		TransformableObj& OwnerTransform;

		bool GetCantMoveState() const{
			if (CantMove) {
				return true;
			}
			else {
				return false;
			}
			return CantMove;
		}

		void MoveTo(Vector2f targetCood);

	private:
		bool CantMove = false;
		Vector2f PrevPos;
		Clock MovingAbilityChecker;
		bool FirstExecute = false;
	};
}