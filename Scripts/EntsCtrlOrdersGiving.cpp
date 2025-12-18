

#include <EntitiesCtrlInputHandler.h>
#include <Engine.h>
#include <GroupSelectionSystem.h>
#include <Extensions.h>
#include <FractionsSystem.h>
#include <DBG_DivineCommander.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Debug;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Physics;

bool EntitiesCtrlInputMode::GivingOrderCondition() {
	return GroupSelectionSystem::GetToPlayertRelOfSelEntities() == Relation::Ally ||
		DBG_DivineCommander::GetActivity();
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
			parEl->TryAddOrder(*new EntityOrder_MoveToPoint(*parEl, *parEl, targetGlobalPos,parEl->GetCollider().GetBoundedCircle().Radius), !isGrouped);
		}
		++begIt;
	}
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
			parEl->TryAddOrder(*ord, !isGrouped);
			delete wtch_ptr;
		}
		++begIt;
	}
}

void EntitiesCtrlInputMode::GiveOrderToSelected_AttackTarget(IAttackableObj& target, bool isGrouped) {
	if (!GivingOrderCondition())
		return;

	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	watch_ptr_handler* wtch_ptr = nullptr;
	IFractionMember* target_fracMem = dynamic_cast<IFractionMember*>(&target);
	EntityOrder_AttackTarget* ord = nullptr;
	for (;begIt != endIt;) {

		parEl = dynamic_cast<Entity*>((*begIt)->GetPtr_t());

		if (parEl != nullptr) {

			wtch_ptr = &target.GetPtr();
			if (wtch_ptr == nullptr)
				throw exception("Cant observe object with watch_ptr");

			ord = new EntityOrder_AttackTarget(*parEl, *parEl, watch_ptr_handler_wr<IAttackableObj>(*wtch_ptr),target_fracMem);
			parEl->TryAddOrder(*ord, !isGrouped);
			delete wtch_ptr;
		}
		++begIt;
	}
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
			parEl->TryAddOrder(*new EntityOrder_Idle(*parEl), !isGrouped);
		}
		++begIt;
	}
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
			parEl->TryAddOrder(*new EntityOrder_Cancel(*parEl), true);
		}
		++begIt;
	}
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
			parEl->TryAddOrder(*new EntityOrder_HoldPosition(*parEl), !isGrouped);
		}
		++begIt;
	}
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
			parEl->TryAddOrder(*new EntityOrder_AttackArea(*parEl, *parEl, targetGlobalPos, parEl->GetCollider().GetBoundedCircle().Radius), !isGrouped);
		}
		++begIt;
	}
}