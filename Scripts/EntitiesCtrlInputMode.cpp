
#include <EntitiesCtrlInputHandler.h>
#include <Engine.h>
#include <GroupSelectionSystem.h>
#include <Extensions.h>
#include <FractionsSystem.h>
#include <DivineCommander.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Physics;

EntitiesCtrlInputMode::EntitiesCtrlInputMode(EntitiesCtrlInputHandler& Owner)
	:Owner(Owner){
}

Vector2f EntitiesCtrlInputMode::GetPosByCursor() {
	Vector2f pos = Engine::GetCursorClampedPos();
	pos = Engine::ScreenPosToGlobalCoord(pos);
	return pos;
}
bool EntitiesCtrlInputMode::TryGetTargetAtPos(Vector2f pos, IPhysicalObject*& target) {
	PhysicsLayer castLayer = (PhysicsLayer)((size_t)PhysicsLayer::Buildings | (size_t)PhysicsLayer::Units);
	target = Engine::GetPhysicsEngine().PointCast(pos, castLayer);
	if (target == nullptr)
		return false;
	else
		return true;
}