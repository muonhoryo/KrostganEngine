
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

//
// 
//HitPoint
//
//
void EntityBattleStats::SetMaxHP(size_t hp) {
	if (hp == 0)
		throw exception("Hit points count must be more than zero");

	MaxHP = hp;

	StatChangedEventHan.Execute(StatType::MaxHP);
}
void EntityBattleStats::SetHPRegenAmount(size_t amount) {
	if (amount >= 0) {
		RegenHP_Amount = amount;
	}

	StatChangedEventHan.Execute(StatType::RegenHP_Amount);
}
void EntityBattleStats::SetHPRegenTick(float tick) {
	if (tick > 0) {
		RegenHP_Tick = tick;
	}

	StatChangedEventHan.Execute(StatType::RegenHP_Tick);
}
//
//
//Moving
//
//
void EntityBattleStats::SetMovingSpeed(float speed){
	if (speed < 0)
		throw exception("Moving spedd cannot be less than zero.");
	
	MovingSpeed = speed;

	StatChangedEventHan.Execute(StatType::MovingSpeed);
}
//
//
//Attack
//
//
void EntityBattleStats::SetAADamage(size_t damage) {
	AADamage = damage;

	StatChangedEventHan.Execute(StatType::AADamage);
}
void EntityBattleStats::SetAASpeed(float speed) {
	if (speed < 0)
		throw exception("AA speed cannot be less than zero");

	AASpeed = speed;

	StatChangedEventHan.Execute(StatType::AASpeed);
}
void EntityBattleStats::SetAARadius(float radius) {
	if (radius < 0)
		throw exception("AA radius cannot be less than zero");

	AARadius = radius;

	StatChangedEventHan.Execute(StatType::AARadius);
}
//
// 
// View
// 
//
void EntityBattleStats::SetAutoAggrRadius(float radius) {
	if (radius < 0)
		throw exception("AutoAggression radius cannot be less than zero");

	AutoAggrRadius = radius;

	StatChangedEventHan.Execute(StatType::AutoAggrRadius);
}