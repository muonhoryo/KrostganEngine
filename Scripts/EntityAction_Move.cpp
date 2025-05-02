
#include <EntityAction_Move.h>
#include <SFML/System.hpp>
#include <Extensions.h>
#include <Engine.h>
#include <Entity.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;

EntityAction_Move::EntityAction_Move(Entity& Owner,Vector2f TargetGlobalCoord)
	:IEntityAction(),
	Owner(Owner),
	TargetGlobalCoord(TargetGlobalCoord){
	DistanceToTarget = FLT_MAX;
}

bool EntityAction_Move::CheckExecCondition() {
	return DistanceToTarget <= eps;
}
void EntityAction_Move::Execute() {
	Vector2f movDirection = TargetGlobalCoord - Owner.GetPosition();
	DistanceToTarget = VectExts::Length(movDirection);
	if (DistanceToTarget <= Owner.BattleStats.GetMovingSpeed()) {
		Owner.SetPosition(TargetGlobalCoord);
		DistanceToTarget = 0;
	}
	else {
		movDirection = VectExts::Normalize(movDirection);
		Vector2f nextPos = Owner.GetPosition() + (movDirection * Owner.BattleStats.GetMovingSpeed());
		Owner.SetPosition(nextPos);
	}
}