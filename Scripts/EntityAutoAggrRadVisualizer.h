#pragma once

#include <EngineCore.h>
#include <CoreVisual_UI.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class EntityAutoAggrRadVisualizer : public CircleVisPrimitive {
	public:
		EntityAutoAggrRadVisualizer(Entity& Owner);
		~EntityAutoAggrRadVisualizer();

		void RenderGraphicAction(RenderWindow& window) override;

	private:
		Entity& Owner;
	};
}