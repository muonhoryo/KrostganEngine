#pragma once

#include <IEntityAction.h>
#include <Entity.h>
#include <SFML/System.hpp>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_MoveTo:public IEntityAction {
	public:
		EntityAction_MoveTo(Entity& Owner);

	protected:
		float DistToTarget;
		Entity& Owner;

		void MoveTo(Vector2f targetCood);
	};
}