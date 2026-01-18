
#include <EntityAction_MoveTo.h>
#include <Extensions.h>
#include <iostream>
#include <Engine.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

EntityAction_MoveTo::EntityAction_MoveTo(OrdersExecutor& Owner)
	:IEntityAction(),
	Owner(Owner),
	PrevPos(Owner.GetGlobalPosition()){

	MovingAbilityChecker.restart();
	DistToTarget = FLT_MAX;
}

void EntityAction_MoveTo::MoveTo(Vector2f targetCoord) {

	if (FirstExecute) {

		MovingAbilityChecker.restart();
		FirstExecute = false;
	}

	if (!CantMove) {
		float time = MovingAbilityChecker.getElapsedTime().asSeconds();
		const GlobalConsts& consts=Engine::GetGlobalConsts();
		float checkTime = consts.Units_MovingAbilityCheckTick;
		if (time >= checkTime) {

			MovingAbilityChecker.restart();
			float immobilityValue = Engine::GetGlobalConsts().Units_ImmobilityCheckValue;
			float prevStep = SquareLength(Owner.GetGlobalPosition() - PrevPos);
			if (prevStep < immobilityValue) {
				CantMove = true;
			}
			PrevPos = Owner.GetGlobalPosition();
		}
	}

	Vector2f movDirection = targetCoord - Owner.GetGlobalPosition();
	DistToTarget = Length(movDirection);
	if (DistToTarget <= Owner.GetBattleStats().GetMovingSpeed()) {
		Owner.SetGlobalPosition(targetCoord);
		DistToTarget = 0;
	}
	else {
		movDirection = Normalize(movDirection);
		Vector2f nextPos = Owner.GetGlobalPosition() + (movDirection * Owner.GetBattleStats().GetMovingSpeed().GetRef_Stat());
		Owner.SetGlobalPosition(nextPos);
	}
}