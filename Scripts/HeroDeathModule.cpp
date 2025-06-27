
#include <HeroObject.h>
#include <LoseScript.h>
#include <WinScript.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::GameTransitions;

void HeroDeathModule::Death() {

	HeroObject* parOwner = dynamic_cast<HeroObject*>(&Owner);
	Fraction frac= parOwner->GetFraction();
	if (frac== Fraction::Player) {

		new LoseScript();
	}
	else if(frac==Fraction::Enemy){

		new WinScript();
	}
	UnitDeathModule::Death();
}