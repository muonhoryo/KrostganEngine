#pragma once

#include <EngineCore.h>
#include <CoreUIUX.h>
#include <VisualOnDeathDestroyer.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class UnitColliderVisualizer : public CircleVisPrimitive{
	public:
		UnitColliderVisualizer(UnitObject& Owner);
		~UnitColliderVisualizer();

		void RenderGraphic(RenderWindow& window) override;

	private:
		UnitObject& Owner;

		void UpdateRadius(float size);
	};
}