
#include <UnitColliderVisualizer.h>
#include <VisualOnDeathDestroyer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

UnitColliderVisualizer::UnitColliderVisualizer(UnitObject& Owner) : CircleVisPrimitive(Vector2f(0,0),1,Color::Green,30),
	Owner(Owner){

	UpdateRadius(Owner.GetScale());
	Owner.GetHPModule().DeathModule.DeathEvent.Add((IEventSubscriber<ObjectDeathEventArgs>*)new VisualOnDeathDestroyer_PostRen(*this, Owner));
}
UnitColliderVisualizer::~UnitColliderVisualizer() {

}

void UnitColliderVisualizer::RenderGraphic(RenderWindow& window) {
	SetCenter(Owner.GetPosition());
	float size = Owner.GetScale();
	if (fabs(size - GetRadius()) > eps)
		UpdateRadius(size);
	CircleVisPrimitive::RenderGraphic(window);
}

void UnitColliderVisualizer::UpdateRadius(float size) {
	SetRadius(size * 0.5f * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution);
}