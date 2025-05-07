#pragma once

namespace KrostganEngine::Physics {
	enum class PhysicsLayer : size_t {
		None = 0,
		Environment = 1,
		Decorations = 2,
		Buildings = 4,
		Units = 8,
		Items = 16,
		Particles=32,
		All=63
	};
}