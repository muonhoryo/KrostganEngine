
#include <UnitColliderVisualizer.h>
#include <VisualOnDeathDestroyer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::UI;

UnitColliderVisualizer::UnitColliderVisualizer(UnitObject& Owner) : CircleVisPrimitive(Vector2f(0,0),1,Color::Green,30),
	Owner(Owner){

	UpdateRadius(Owner.GetGlobalScale_Sng());
	Owner.GetHPModule().DeathModule.DeathEvent.Add(*(IEventSubscriber<const ObjectDeathEventArgs>*)new VisualOnDeathDestroyer(*this, Owner));
}
UnitColliderVisualizer::~UnitColliderVisualizer() {

}

void UnitColliderVisualizer::RenderGraphicAction(RenderWindow& window) {
	SetCenter(Owner.GetGlobalPosition());
	float size = Owner.GetGlobalScale_Sng();
	if (fabs(size - GetRadius()) > eps)
		UpdateRadius(size);
	CircleVisPrimitive::RenderGraphicAction(window);
}

void UnitColliderVisualizer::UpdateRadius(float size) {
	SetRadius(size * 0.5f * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution);
}