
#include <HeroObject.h>
#include <LoseScript.h>
#include <WinScript.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::GameTransitions;

void HeroDeathModule::Death() {

	HeroObject* parOwner = dynamic_cast<HeroObject*>(&Owner);
	FractionWrapper frac= parOwner->GetFraction();
	if (frac.Fraction_.Index == FractionsSystem::PLAYER_FRACTION) {

		new LoseScript();
	}
	else if(FractionsSystem::GetRelationToPlayer(frac) == Relation::Enemy){

		new WinScript();
	}
	UnitDeathModule::Death();
}