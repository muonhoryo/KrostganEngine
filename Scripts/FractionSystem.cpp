
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
Relation FractionsSystem::GetRelationToPlayer(Fraction objFrac) {
	return GetRelation(objFrac, Fraction::Player);
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
	return FractionsSystem::GetRelationColor(GetRelationToPlayer(objFrac));
}
/// <summary>
/// Return empty string in heap if frac is invalid
/// </summary>
/// <param name="frac"></param>
/// <returns></returns>
const string& FractionsSystem::GetNameOfFraction(Fraction frac) {
	for (auto it = FractionNames.begin();it != FractionNames.end();++it) {
		if ((*it).second == frac)
			return (*it).first;
	}
	return *new string("");
}