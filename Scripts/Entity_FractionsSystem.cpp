
#include <Entity.h>
#include <WarFogObserversManager.h>
#include <GroupSelectionSystem.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

Fraction Entity::GetFraction() const {
	return EntityFraction;
}

void Entity::SetFraction(Fraction fraction) {
	if (fraction == GetFraction()) {
		return;
	}

	ChangeFractionEvArgs evArgs = ChangeFractionEvArgs(*this, GetFraction(), fraction);
	EntityFraction = fraction;
	SetObservingActive(FractionsSystem::GetRelationToPlayer(fraction) == Relation::Ally);
	WarFogObserversManager::GetInstance()->Set_NeedToSort();
	SetColor(FractionsSystem::GetRelationToPlayerColor(fraction));
	GroupSelectionSystem::Remove(*this);
	GetAutoAggrModule().Restart();
	ResetOrdersQueue();
	MemberHasChangedFracEvHandler.Execute(evArgs);
}