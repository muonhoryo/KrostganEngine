
#include <DivineCommander.h>
#include <GroupSelectionSystem.h>

using namespace KrostganEngine::Debug;
using namespace KrostganEngine::EntitiesControl;

void DivineCommander::TurnOn() {
	if (!IsActive) {
		IsActive = true;
	}
}
void DivineCommander::TurnOff() {
	if (IsActive) {
		IsActive = false;
		GroupSelectionSystem::Clear();
	}
}