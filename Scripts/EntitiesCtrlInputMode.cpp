
#include <EntitiesCtrlInputHandler.h>
#include <Engine.h>
#include <GroupSelectionSystem.h>
#include <Extensions.h>
#include <FractionsSystem.h>

using namespace KrostganEngine;
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

void EntitiesCtrlInputMode::GiveOrderToSelected_MoveToPoint(Vector2f targetGlobalPos) {
	if (GroupSelectionSystem::GeToPlayertRelOfSelEntities() != Relation::Ally)
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>(*begIt);
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_MoveToPoint(*parEl,*parEl, targetGlobalPos), true);
		}
		++begIt;
	}
	cout << "Give an order: Move to " << ToString<float>(targetGlobalPos) << endl;
}
void EntitiesCtrlInputMode::GiveOrderToSelected_AttackTarget(IAttackableObj& target) {
	if (GroupSelectionSystem::GeToPlayertRelOfSelEntities() != Relation::Ally)
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>(*begIt);
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_AttackTarget(*parEl, *parEl,target), true);
		}
		++begIt;
	}
	cout << "Give an order: Attack target " << endl;
}