
#include <HeroObject.h>
#include <LoseScript.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::GameTransitions;

void HeroDeathModule::Death() {

	new LoseScript();
	UnitDeathModule::Death();
}