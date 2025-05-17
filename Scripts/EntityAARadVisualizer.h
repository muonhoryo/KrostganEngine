#pragma once

#include <EngineCore.h>
#include <CoreUIUX.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class EntityAARadVisualizer : public CircleVisPrimitive {
	public:
		EntityAARadVisualizer(const Entity& Owner);
		~EntityAARadVisualizer();

		void RenderGraphic(RenderWindow& window) override;

	private:
		const Entity& Owner;
	};
}