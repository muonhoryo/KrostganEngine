
#include <DBG_DivineCommander.h>
#include <GroupSelectionSystem.h>

using namespace KrostganEngine::Debug;
using namespace KrostganEngine::EntitiesControl;

void DBG_DivineCommander::TurnOn() {
	if (!IsActive) {
		IsActive = true;
	}
}
void DBG_DivineCommander::TurnOff() {
	if (IsActive) {
		IsActive = false;
		GroupSelectionSystem::Clear();
	}
}