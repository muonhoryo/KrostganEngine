
#include <IAttackableObj.h>

using namespace KrostganEngine::GameObjects;

IHitPointModule::IHitPointModule(IDeathModule& DeathModule, TakeDamageAnimation& TakeDmgAnim)
	:DeathModule(DeathModule), TakeDmgAnim(TakeDmgAnim){
}

IHitPointModule::~IHitPointModule() {

	delete& DeathModule;
}

void IHitPointModule::TakeDamage(const AttackHitInfo& attInfo) {
	size_t dmg = TakeDamage_Action(attInfo);
	if (dmg != 0)
		TakeDmgAnim.OnTakeDmg(attInfo, dmg);
}