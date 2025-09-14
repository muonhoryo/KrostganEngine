

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

bool EntitiesCtrlInputMode::GivingOrderCondition() {
	return GroupSelectionSystem::GetToPlayertRelOfSelEntities() == Relation::Ally ||
		DivineCommander::GetActivity();
}

void EntitiesCtrlInputMode::GiveOrderToSelected_MoveToPoint(Vector2f targetGlobalPos, bool isGrouped) {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {

		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_MoveToPoint(*parEl, *parEl, targetGlobalPos,parEl->GetCollider().GetBoundedCircle().Radius), !isGrouped);
		}
		++begIt;
	}
	cout << "Give an order: Move to " << to_string<float>(targetGlobalPos) << endl;
}

void EntitiesCtrlInputMode::GiveOrderToSelected_FollowObject(ITransformableObj& target, bool isGrouped) {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	watch_ptr_handler* wtch_ptr = nullptr;
	EntityOrder_FollowTarget* ord = nullptr;
	for (;begIt != endIt;) {

		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());

		if (parEl != nullptr) {

			wtch_ptr = &target.GetPtr();
			if (wtch_ptr == nullptr)
				throw exception("Cant observe object with watch_ptr");

			ord = new EntityOrder_FollowTarget(*parEl, *parEl, watch_ptr_handler_wr_c<WorldTransfObj>(*wtch_ptr));
			parEl->TryAddOrder(ord, !isGrouped);
			delete wtch_ptr;
		}
		++begIt;
	}
	cout << "Give an order: Follow target " << endl;
}

void EntitiesCtrlInputMode::GiveOrderToSelected_AttackTarget(IAttackableObj& target, bool isGrouped) {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	watch_ptr_handler* wtch_ptr = nullptr;
	EntityOrder_AttackTarget* ord = nullptr;
	for (;begIt != endIt;) {

		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());

		if (parEl != nullptr) {

			wtch_ptr = &target.GetPtr();
			if (wtch_ptr == nullptr)
				throw exception("Cant observe object with watch_ptr");

			ord = new EntityOrder_AttackTarget(*parEl, *parEl, watch_ptr_handler_wr<IAttackableObj>(*wtch_ptr));
			parEl->TryAddOrder(ord, !isGrouped);
			delete wtch_ptr;
		}
		++begIt;
	}
	cout << "Give an order: Attack target " << endl;
}

void EntitiesCtrlInputMode::GiveOrderToSelected_Idle(bool isGrouped) {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_Idle(*parEl), !isGrouped);
		}
		++begIt;
	}
	cout << "Give an order: Idle " << endl;
}

void EntitiesCtrlInputMode::GiveOrderToSelected_Cancel() {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_Cancel(*parEl), true);
		}
		++begIt;
	}
	cout << "Give an order: Cancel " << endl;
}

void EntitiesCtrlInputMode::GiveOrderToSelected_HoldPosition(bool isGrouped) {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_HoldPosition(*parEl), !isGrouped);
		}
		++begIt;
	}
	cout << "Give an order: Hold position" << endl;
}
void EntitiesCtrlInputMode::GiveOrderToSelected_AttackArea(Vector2f targetGlobalPos, bool isGrouped) {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_AttackArea(*parEl, *parEl, targetGlobalPos), !isGrouped);
		}
		++begIt;
	}
	cout << "Give an order: Attack area on way to " << to_string<float>(targetGlobalPos) << endl;
}