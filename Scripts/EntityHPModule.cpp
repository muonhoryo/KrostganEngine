
#include <EntityHPModule.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityHPModule::EntityHPModule(IDeathModule& DeathModule, EntityBattleStats& BattleStats, HPRegenModule* RegenModule) : IHitPointModule(DeathModule),
	BattleStats(BattleStats),
	RegenModule(RegenModule){
}

void EntityHPModule::TakeDamage(AttackInfo attInfo) {
	size_t currHP = BattleStats.GetCurrentHP();
	if (currHP <= attInfo.DealtDmg)
		DeathModule.Death();
	else {
		BattleStats.SetCurrentHP(currHP - attInfo.DealtDmg);
		cout << "Take damage " << attInfo.DealtDmg << ": remained " << BattleStats.GetCurrentHP() << " / " << BattleStats.GetMaxHP()<<" health" << endl;
	}
}