
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
	IndicatorFill&		HPBar,
	TakeDamageAnimation& TakeDmgAnim)

	:IHitPointModule(DeathModule,TakeDmgAnim),
		BattleStats(BattleStats),
		HPBar(HPBar),
		MaxHP(BattleStats.GetMaxHP()){

	Subscriber = new StatChangedEvSubs(*this);
	RestoreHealth();
	BattleStats.StatChangedEvent.Add(*Subscriber);
}
EntityHPModule::~EntityHPModule() {

	if (RegenModule != nullptr)
		delete RegenModule;

	BattleStats.StatChangedEvent.Remove(*Subscriber);
	delete Subscriber;
}

size_t EntityHPModule::TakeDamage_Action(const AttackHitInfo& attInfo) {
	
	size_t totalDmg;
	if (CurrentHP <= attInfo.DealtDmg) {
		
		totalDmg = CurrentHP;
		SetCurrentHP(0);
		DeathModule.Death();
	}
	else {
		totalDmg = attInfo.DealtDmg;
		SetCurrentHP(CurrentHP - attInfo.DealtDmg);
	}
	return totalDmg;
}
void EntityHPModule::SetCurrentHP	(size_t hp) {

	size_t maxHP = GetMaxHP();

	if (hp > maxHP)
		CurrentHP = maxHP;
	else
		CurrentHP = hp;

	HPBar.SetFillness((float)CurrentHP / (float)maxHP);
	ChangedHPEvHandler.Execute();
}
void EntityHPModule::RestoreHealth	() {

	SetCurrentHP(GetMaxHP());
}
void EntityHPModule::SetRegenModule(HPRegenModule* Module) {
	
	if (RegenModule != nullptr)
		delete RegenModule;

	RegenModule = Module;
}