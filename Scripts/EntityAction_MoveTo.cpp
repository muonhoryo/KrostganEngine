
#include <EntityAction_MoveTo.h>
#include <Extensions.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

EntityAction_MoveTo::EntityAction_MoveTo(Entity& Owner) 
	:IEntityAction(),
	Owner(Owner){
	DistToTarget = FLT_MAX;
}

void EntityAction_MoveTo::MoveTo(Vector2f targetCoord) {
	Vector2f movDirection = targetCoord - Owner.GetPosition();
	DistToTarget = Length(movDirection);
	if (DistToTarget <= Owner.GetBattleStats().GetMovingSpeed()) {
		Owner.SetPosition(targetCoord);
		DistToTarget = 0;
	}
	else {
		movDirection = Normalize(movDirection);
		Vector2f nextPos = Owner.GetPosition() + (movDirection * Owner.GetBattleStats().GetMovingSpeed());
		Owner.SetPosition(nextPos);
	}
}