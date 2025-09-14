
#include <UnitColliderVisualizer.h>
#include <VisualOnDeathDestroyer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

UnitColliderVisualizer::UnitColliderVisualizer(UnitObject& Owner) : CircleVisPrimitive(Vector2f(0,0),1,Color::Green,30),
	Owner(Owner){

	UpdateRadius(Owner.GetGlobalScale_Sin());
	Owner.GetHPModule().DeathModule.DeathEvent.Add(*(IEventSubscriber<ObjectDeathEventArgs>*)new VisualOnDeathDestroyer_PostRen(*this, Owner));
}
UnitColliderVisualizer::~UnitColliderVisualizer() {

}

void UnitColliderVisualizer::RenderGraphicAction(RenderWindow& window) {
	SetCenter(Owner.GetGlobalPosition());
	float size = Owner.GetGlobalScale_Sin();
	if (fabs(size - GetRadius()) > eps)
		UpdateRadius(size);
	CircleVisPrimitive::RenderGraphic(window);
}

void UnitColliderVisualizer::UpdateRadius(float size) {
	SetRadius(size * 0.5f * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution);
}