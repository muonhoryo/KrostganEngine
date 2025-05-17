#pragma once

#include <EngineCore.h>
#include <CoreUIUX.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class EntityAutoAggrRadVisualizer : public CircleVisPrimitive {
	public:
		EntityAutoAggrRadVisualizer(const Entity& Owner);
		~EntityAutoAggrRadVisualizer();

		void RenderGraphic(RenderWindow& window) override;

	private:
		const Entity& Owner;
	};
}