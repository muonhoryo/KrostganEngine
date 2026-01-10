#pragma once

namespace KrostganEngine::EntitiesControl {
	enum class EntityOrderType {
		MovingToPoint,
		FollowTarget,
		AttackTarget,
		AttackArea,
		HoldPosition,
		Cancel,
		Idle,
		AbilityUsing
	};
}