
#include <IHitPointModule.h>

using namespace KrostganEngine::GameObjects;

ObjectDeathEventArgs::ObjectDeathEventArgs(){}

IHitPointModule::IHitPointModule() 
	:DeathEvHandler(EventHandler<ObjectDeathEventArgs>(DeathEvent)){
}