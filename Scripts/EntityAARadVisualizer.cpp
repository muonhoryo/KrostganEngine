
#include <EntityAARadVisualizer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;

EntityAARadVisualizer::EntityAARadVisualizer(Entity& Owner) : CircleVisPrimitive(Vector2f(0, 0), 1, Color::Red, 30),
Owner(Owner) {

	Owner.GetHPModule().DeathModule.DeathEvent.Add(*(IEventSubscriber<const ObjectDeathEventArgs>*)new VisualOnDeathDestroyer(*this, Owner));
}
EntityAARadVisualizer::~EntityAARadVisualizer() {

}

void EntityAARadVisualizer::RenderGraphicAction(RenderWindow& window) {
	SetCenter(Owner.GetGlobalPosition());
	float size = Owner.GetBattleStats().GetAAStats()->GetRange();
	if (abs(size - GetRadius()) > eps)
		SetRadius(size);
	CircleVisPrimitive::RenderGraphic(window);
}