
#include <IAttackableObj.h>

using namespace KrostganEngine::GameObjects;

ObjectDeathEventArgs::ObjectDeathEventArgs() {}

IDeathModule::IDeathModule(IAttackableObj& Owner) : DeathEvHandler(EventHandler<ObjectDeathEventArgs>(DeathEvent)),
	Owner(Owner){

}
