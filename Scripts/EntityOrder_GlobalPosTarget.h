#pragma once

#include <IEntityOrder.h>
#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_GlobalPosTarget {
	public:
		const Vector2f TargetGlobalPos;

	protected:
		EntityOrder_GlobalPosTarget(Vector2f TargetGlobalPos) :TargetGlobalPos(TargetGlobalPos) {}
	};
}