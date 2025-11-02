#pragma once

namespace KrostganEngine::GameObjects {
	struct AttackHitInfo {

		AttackHitInfo(size_t DealtDmg)
			:DealtDmg(DealtDmg)
		{}

		size_t DealtDmg;
	};
}