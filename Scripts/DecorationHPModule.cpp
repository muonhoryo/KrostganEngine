
#include <DecorationHPModule.h>

using namespace KrostganEngine::GameObjects;

DecorationHPModule::DecorationHPModule(
	size_t CurrentHP,
	size_t MaxHP,
	IDeathModule& DeathModule,
	TakeDamageAnimation& TakeDmgAnim) 
		:IHitPointModule(DeathModule,TakeDmgAnim),
			CurrentHP(CurrentHP),
			MaxHP(MaxHP)
{}

DecorationHPModule::~DecorationHPModule(){
	
}

size_t	DecorationHPModule::TakeDamage_Action(const AttackHitInfo& attInfo) {

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
void	DecorationHPModule::SetCurrentHP(size_t hp) {

	size_t maxHP = GetMaxHP();

	if (hp > maxHP)
		CurrentHP = maxHP;
	else
		CurrentHP = hp;

	ChangedHPEvHandler.Execute();
}
void	DecorationHPModule::RestoreHealth() {

	SetCurrentHP(GetMaxHP());
}