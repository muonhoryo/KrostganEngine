
#include <EntityHPModule.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityHPModule::EntityHPModule(EntityBattleStats& BattleStats)
	:BattleStats(BattleStats){
}

void EntityHPModule::TakeDamage(AttackInfo attInfo) {
	size_t currHP = BattleStats.GetCurrentHP();
	if (currHP <= attInfo.DealtDmg)
		Death();
	else {
		BattleStats.SetCurrentHP(currHP - attInfo.DealtDmg);
		cout << "Take damage " << attInfo.DealtDmg << ": remained " << BattleStats.GetCurrentHP() << " / " << BattleStats.GetMaxHP()<<" health" << endl;
	}
}
void EntityHPModule::Death() {
	BattleStats.RestoreHealth();
	ObjectDeathEventArgs& args = *new ObjectDeathEventArgs();
	DeathEvHandler.Execute(args);
	delete &args;
	cout << "Death confirmed. Rescuing started" << endl;
}