#pragma once

#include <Entity.h>
#include <SFML/System.hpp>
#include <IEntityAction.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_Move :public IEntityAction {
	public:
		EntityAction_Move(Entity& Owner,Vector2f TargetGlobalCoord);

		bool CheckExecCondition() override;
		void Execute() override;

		const Vector2f TargetGlobalCoord;
	private:
		float DistanceToTarget;
		Entity& Owner;
	};
}