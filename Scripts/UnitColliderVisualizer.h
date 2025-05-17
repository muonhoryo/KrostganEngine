#pragma once

#include <EngineCore.h>
#include <CoreUIUX.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class UnitColliderVisualizer : public CircleVisPrimitive{
	public:
		UnitColliderVisualizer(const TransformableObj& Owner);
		~UnitColliderVisualizer();

		void RenderGraphic(RenderWindow& window) override;

	private:
		const TransformableObj& Owner;
	};
}