
#include <UnitColliderVisualizer.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Physics;

UnitColliderVisualizer::UnitColliderVisualizer(const TransformableObj& Owner) : CircleVisPrimitive(Vector2f(0,0),1,Color::Green,30),
	Owner(Owner){

}
UnitColliderVisualizer::~UnitColliderVisualizer() {

}

void UnitColliderVisualizer::RenderGraphic(RenderWindow& window) {
	SetCenter(Owner.GetPosition());
	float size = Owner.GetScale();
	if (abs(size - GetRadius()) > eps)
		SetRadius(size * 0.5f * Engine::GetGlobalConsts().GameObjs_OneSizeSpriteResolution);
	CircleVisPrimitive::RenderGraphic(window);
}