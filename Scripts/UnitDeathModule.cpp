
#include <UnitObject.h>
#include <UnitDeathEffect.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Visual;

void UnitDeathModule::Death() {

	new UnitDeathEffect(*dynamic_cast<UnitObject*>(&Owner));
	EntityDeathModule::Death();
}