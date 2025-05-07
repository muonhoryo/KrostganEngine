
#include <AutoAttackModule.h>

using namespace KrostganEngine::GameObjects;

AutoAttackModule::AutoAttackModule():ICallbackRec_Upd(),
	Target(nullptr){
	RemReloadTime = 0;
}

IAttackableObj& AutoAttackModule::GetCurrentTarget() {
	return *Target;
}

float AutoAttackModule::GetRemReloadTime() const {
	return RemReloadTime;
}

void AutoAttackModule::Update(CallbackRecArgs_Upd args) {
	if (RemReloadTime > 0)
		RemReloadTime -= args.LastFrameDeltaTime;
}