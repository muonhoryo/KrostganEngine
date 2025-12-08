
#include <EntityAutoAggrRadVisualizer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;

EntityAutoAggrRadVisualizer::EntityAutoAggrRadVisualizer(Entity& Owner) : CircleVisPrimitive(Vector2f(0, 0), 1, Color::Yellow, 30),
Owner(Owner) {

	Owner.GetHPModule().DeathModule.DeathEvent.Add(*(IEventSubscriber<const ObjectDeathEventArgs>*)new VisualOnDeathDestroyer(*this, Owner));
}
EntityAutoAggrRadVisualizer ::~EntityAutoAggrRadVisualizer() {

}

void EntityAutoAggrRadVisualizer::RenderGraphicAction(RenderWindow& window) {
	SetCenter(Owner.GetGlobalPosition());
	float size = Owner.GetBattleStats().GetAutoAggrRange();
	if (abs(size - GetRadius()) > eps)
		SetRadius(size);
	CircleVisPrimitive::RenderGraphicAction(window);
}