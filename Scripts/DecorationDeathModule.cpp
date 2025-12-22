
#include <DecorationDeathModule.h>

using namespace KrostganEngine::GameObjects;

DecorationDeathModule::DecorationDeathModule(IAttackableObj& owner) 
	:IDeathModule(owner){

}

void DecorationDeathModule::Death() {

	if (IsDead)
		return;

	IsDead = true;

	ObjectDeathEventArgs& args = *new ObjectDeathEventArgs();
	DeathEvExecute(args);
	delete& args;

	new DelayedDeath(Owner);
}