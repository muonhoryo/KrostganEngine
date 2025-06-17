
#include <IAttackableObj.h>

using namespace KrostganEngine::GameObjects;

IHitPointModule::IHitPointModule(IDeathModule& DeathModule)
	:DeathModule(DeathModule){
}