
#include <FractionsSystem.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::EntitiesControl;

Relation FractionsSystem::GetRelation(Fraction objFrac, Fraction subjFrac) {
	if (objFrac == subjFrac)
		return Relation::Ally;
	else {
		if (objFrac == Fraction::Neutral || subjFrac == Fraction::Neutral)
			return Relation::Neutral;
		else
			return Relation::Enemy;
	}
}
Color FractionsSystem::GetRelationColor(Relation rel) {
	switch (rel)
	{
	case KrostganEngine::EntitiesControl::Relation::Ally:
		return Color::Green;
	case KrostganEngine::EntitiesControl::Relation::Neutral:
		return Color::Yellow;
	case KrostganEngine::EntitiesControl::Relation::Enemy:
		return Color::Red;
	default:
		throw exception("Undefined relation: " + (int)rel);
	}
}
Color FractionsSystem::GetRelationToPlayerColor(Fraction objFrac) {
	return FractionsSystem::GetRelationColor(FractionsSystem::GetRelation(objFrac, Fraction::Player));
}