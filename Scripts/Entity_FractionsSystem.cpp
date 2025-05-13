
#include <Entity.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

Fraction Entity::GetFraction() const {
	return EntityFraction;
}

Color Entity::GetSprColorFromFraction(Fraction frac) {
	return FractionsSystem::GetRelationColor(FractionsSystem::GetRelation(frac, Fraction::Player));
}