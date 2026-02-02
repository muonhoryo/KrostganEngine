#pragma once

#include <_EngineCore.h>
#include <_CoreVisual_UI.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class EntityAARadVisualizer : public CircleVisPrimitive {
	public:
		EntityAARadVisualizer(Entity& Owner);
		~EntityAARadVisualizer();

		void RenderGraphicAction(RenderWindow& window) override;

	private:
		Entity& Owner;
	};
}