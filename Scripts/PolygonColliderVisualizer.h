#pragma once

#include <_EngineCore.h>
#include <_CoreVisual_UI.h>
#include <VisualOnDeathDestroyer.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Debug {
	class PolygonColliderVisualizer : public LinesVisPrimitive {
	public:
		PolygonColliderVisualizer(PolygonCollShape& Owner);
		virtual ~PolygonColliderVisualizer();

		void RenderGraphicAction(RenderWindow& window) override;

	private:
		PolygonCollShape& Owner;

		vector<Vector2f>& Init_GetPoints(PolygonCollShape& owner);
	};
}