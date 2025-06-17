
#include <Entity.h>
#include <iostream>
#include <CallbackDelegates.h>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Visual;

EntityDeathModule::EntityDeathModule(Entity& Owner) : IDeathModule((IAttackableObj&)Owner),
	ParOwner(Owner){

}


void EntityDeathModule::Death() {

	IsDead = true;
	ParOwner.SelectionOff();
	ParOwner.ProhibitOrdersExecution();

	ObjectDeathEventArgs& args = *new ObjectDeathEventArgs();
	DeathEvHandler.Execute(args);
	delete& args;
}