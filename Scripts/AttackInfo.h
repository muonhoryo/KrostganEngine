#pragma once

namespace KrostganEngine::GameObjects {
	struct AttackInfo {

		AttackInfo(size_t DealtDmg)
			:DealtDmg(DealtDmg)
		{}

		size_t DealtDmg;
	};
}