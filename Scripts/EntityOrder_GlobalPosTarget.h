#pragma once

#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_GlobalPosTarget {
	public:
		virtual ~EntityOrder_GlobalPosTarget(){}

		const Vector2f TargetGlobalPos;

	protected:
		EntityOrder_GlobalPosTarget(Vector2f TargetGlobalPos) :TargetGlobalPos(TargetGlobalPos) {}
	};
}