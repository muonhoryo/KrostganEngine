
#include <EntityHPModule.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityHPModule::EntityHPModule(EntityBattleStats& BattleStats)
	:BattleStats(BattleStats){
}

void EntityHPModule::TakeDamage(size_t damage) {
	size_t currHP = BattleStats.GetCurrentHP();
	if (currHP <= damage)
		Death();
	else {
		BattleStats.SetCurrentHP(currHP - damage);
		cout << "Take damage " << damage << ": remained " << BattleStats.GetCurrentHP() << " / " << BattleStats.GetMaxHP()<<" health" << endl;
	}
}
void EntityHPModule::Death() {
	BattleStats.RestoreHealth();
	ObjectDeathEventArgs& args = *new ObjectDeathEventArgs();
	DeathEvHandler.Execute(args);
	delete &args;
	cout << "Death confirmed. Rescuing started" << endl;
}