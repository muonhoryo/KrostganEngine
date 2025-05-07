
#include <EntitiesCtrlInputHandler.h>
#include <Engine.h>
#include <GroupSelectionSystem.h>
#include <Extensions.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::PlayerControl;

EntitiesCtrlInputMode::EntitiesCtrlInputMode(EntitiesCtrlInputHandler& Owner)
	:Owner(Owner){
}

void EntitiesCtrlInputMode::GiveOrderToSelected_MoveToPoint() {
	Vector2f movingTarget = Engine::GetCursorClampedPos();
	movingTarget = Engine::ScreenPosToGlobalCoord(movingTarget);
	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>(*begIt);
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_MoveToPoint(*parEl, movingTarget), true);
		}
		++begIt;
	}
	cout << "Give an order: Move to " << ToString(movingTarget) << endl;
}
void EntitiesCtrlInputMode::GiveOrderToSelected_AttackTarget() {
	Vector2f cursorPos = Engine::GetCursorClampedPos();
	cursorPos = Engine::ScreenPosToGlobalCoord(cursorPos);
	PhysicsLayer castLayer = (PhysicsLayer)((size_t)PhysicsLayer::Buildings | (size_t)PhysicsLayer::Units);
	IPhysicalObject* physTarget = Engine::GetPhysicsEngine().PointCast(cursorPos, castLayer);
	if (physTarget == nullptr)
		return;
	IAttackableObj* target = dynamic_cast<IAttackableObj*>(physTarget);
	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>(*begIt);
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_AttackTarget(*parEl, *target), true);
		}
		++begIt;
	}
	cout << "Give an order: Attack target " << endl;
}