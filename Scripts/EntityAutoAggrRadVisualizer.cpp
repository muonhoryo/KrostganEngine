
#include <EntityAutoAggrRadVisualizer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;

EntityAutoAggrRadVisualizer::EntityAutoAggrRadVisualizer(const Entity& Owner) : CircleVisPrimitive(Vector2f(0, 0), 1, Color::Yellow, 30),
Owner(Owner) {

}
EntityAutoAggrRadVisualizer ::~EntityAutoAggrRadVisualizer() {

}

void EntityAutoAggrRadVisualizer::RenderGraphic(RenderWindow& window) {
	SetCenter(Owner.GetPosition());
	float size = Owner.GetBattleStats().GetAutoAggrRadius();
	if (abs(size - GetRadius()) > eps)
		SetRadius(size);
	CircleVisPrimitive::RenderGraphic(window);
}