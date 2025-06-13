
#include <AutoAttackModule.h>

using namespace KrostganEngine::GameObjects;

AutoAttackModule::AutoAttackModule(AutoAttackAnimation& AAAnimation):ICallbackRec_Upd(),
	Target(nullptr),
	AAAnimation(AAAnimation)
{}
AutoAttackModule::~AutoAttackModule() {
	delete &AAAnimation;
}

IAttackableObj* AutoAttackModule::GetCurrentTarget() {
	return Target;
}

float AutoAttackModule::GetRemReloadTime() const {
	return RemReloadTime;
}

void AutoAttackModule::Update(CallbackRecArgs_Upd args) {
	if (RemReloadTime > 0)
		RemReloadTime -= args.LastFrameDeltaTime;
}