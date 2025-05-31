#pragma once

namespace KrostganEngine::EntitiesControl {
	enum class EntityOrderType {
		MovingToPoint,
		FollowTarget,
		AttackTarget,
		HoldPosition,
		Cancel,
		Idle
	};
}