
#include <EntityAARadVisualizer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;

EntityAARadVisualizer::EntityAARadVisualizer(const Entity& Owner) : CircleVisPrimitive(Vector2f(0, 0), 1, Color::Red, 30),
Owner(Owner) {

}
EntityAARadVisualizer::~EntityAARadVisualizer() {

}

void EntityAARadVisualizer::RenderGraphic(RenderWindow& window) {
	SetCenter(Owner.GetPosition());
	float size = Owner.GetBattleStats().GetAARadius();
	if (abs(size - GetRadius()) > eps)
		SetRadius(size);
	CircleVisPrimitive::RenderGraphic(window);
}