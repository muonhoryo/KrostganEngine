
#include <OrdersSystemInteraction.h>
#include <GroupSelectionSystem.h>
#include <EntityOrder_MoveToPoint.h>
#include <iostream>
#include <Extensions.h>
#include <Engine.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::PlayerControl;
using namespace KrostganEngine::EntitiesControl;

OrdersSystemInteraction::OrdersSystemInteraction() {
}

void OrdersSystemInteraction::Update(CallbackRecArgs_Upd args) {
	for (auto& input : args.PlayerInput) {
		if (input.type == Event::MouseButtonPressed) {
			if (input.key.code == Mouse::Right) {
				GiveOrderToSelected_MoveToPoint();
			}
		}
	}
}

void OrdersSystemInteraction::GiveOrderToSelected_MoveToPoint() {
	Vector2f movingTarget = Engine::GetCursorClampedPos();
	movingTarget = Engine::ScreenPosToGlobalCoord(movingTarget);
	auto begIt = GroupSelectionSystem::GetEntitiesBegIter();
	auto endIt = GroupSelectionSystem::GetEntitiesEndIter();
	Entity* parEl;
	for (;begIt != endIt;) {
		parEl = dynamic_cast<Entity*>(*begIt);
		if (parEl != nullptr) {
			parEl->TryAddOrder(new EntityOrder_MoveToPoint(*parEl, movingTarget),true);
		}
		++begIt;
	}
	cout << "Give an order: Move to " << VectExts::ToString(movingTarget) << endl;
}