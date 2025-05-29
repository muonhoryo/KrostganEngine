#pragma once

namespace KrostganEngine::EntitiesControl {
	enum class EntityOrderType {
		MovingToPoint,
		AttackTarget,
		HoldPosition,
		Cancel
	};
}