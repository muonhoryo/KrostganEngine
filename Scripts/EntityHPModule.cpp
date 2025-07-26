
#include <EntityHPModule.h>
#include <iostream>
#include <Engine.h>

using namespace std;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

EntityHPModule::EntityHPModule(
	IDeathModule&		DeathModule, 
	EntityBattleStats&	BattleStats,
	IndicatorFill&		HPBar)

	:IHitPointModule(DeathModule),
		BattleStats(BattleStats),
		HPBar(HPBar){

	Subscriber = new StatChangedEvSubs(*this);
	RestoreHealth();
	BattleStats.StatChangedEvent.Add(Subscriber);
}
EntityHPModule::~EntityHPModule() {

	if (RegenModule != nullptr)
		delete RegenModule;

	BattleStats.StatChangedEvent.Remove(Subscriber);
	delete Subscriber;
}

void EntityHPModule::TakeDamage		(AttackInfo attInfo) {
	
	if (CurrentHP<= attInfo.DealtDmg)
		DeathModule.Death();
	else {
		SetCurrentHP(CurrentHP - attInfo.DealtDmg);
		cout << "Take damage " << attInfo.DealtDmg << ": remained " << CurrentHP << " / " << BattleStats.GetMaxHP()<<" health" << endl;
	}
}
void EntityHPModule::SetCurrentHP	(size_t hp) {

	if (hp == 0)
		throw exception("Hit points count must be more than zero");

	size_t maxHP = GetMaxHP();

	if (hp > maxHP)
		CurrentHP = maxHP;
	else
		CurrentHP = hp;

	HPBar.SetFillness((float)CurrentHP / (float)maxHP);
}
void EntityHPModule::RestoreHealth	() {

	SetCurrentHP(GetMaxHP());
}
void EntityHPModule::SetRegenModule(HPRegenModule* Module) {
	
	if (RegenModule != nullptr)
		delete RegenModule;

	RegenModule = Module;
}