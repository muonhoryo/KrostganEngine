
#include <Entity.h>
#include <WarFogObserversManager.h>
#include <GroupSelectionSystem.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

FractionWrapper Entity::GetFraction() const {
	return EntityFraction;
}

void Entity::SetFraction(FractionWrapper fraction) {
	if (fraction == GetFraction()) {
		return;
	}

	ChangeFractionEvArgs evArgs = ChangeFractionEvArgs(*this, GetFraction(), fraction);
	EntityFraction = fraction;
	SetObservingActive(FractionsSystem::GetRelationToPlayer(fraction) == Relation::Ally);
	WarFogObserversManager::GetInstance()->Set_NeedToSort();
	SetColor(EntityFraction.Fraction_.FracColor);
	GroupSelectionSystem::Remove(*this);
	GetAutoAggrModule().Restart();
	ResetOrdersQueue();
	OnChangeFraction(fraction);
	MemberHasChangedFracEvHandler.Execute(evArgs);
}