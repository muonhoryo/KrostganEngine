
#include <EntityAction_MoveTo.h>
#include <Extensions.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

EntityAction_MoveTo::EntityAction_MoveTo(OrdersExecutor& Owner,TransformableObj& OwnerTransform)
	:IEntityAction(),
	Owner(Owner),
	OwnerTransform(OwnerTransform){
	DistToTarget = FLT_MAX;
}

void EntityAction_MoveTo::MoveTo(Vector2f targetCoord) {
	Vector2f movDirection = targetCoord - OwnerTransform.GetPosition();
	DistToTarget = Length(movDirection);
	if (DistToTarget <= Owner.GetBattleStats().GetMovingSpeed()) {
		OwnerTransform.SetPosition(targetCoord);
		DistToTarget = 0;
	}
	else {
		movDirection = Normalize(movDirection);
		Vector2f nextPos = OwnerTransform.GetPosition() + (movDirection * Owner.GetBattleStats().GetMovingSpeed());
		OwnerTransform.SetPosition(nextPos);
	}
}