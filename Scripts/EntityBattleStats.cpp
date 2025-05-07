
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityBattleStats::EntityBattleStats() 
{
	MovingSpeed = 0;
	MaxHP = 1;
	CurrentHP = 1;
	AADamage = 0;
	AASpeed = 0;
	AARadius = 0;
}

//
// 
//HitPoint
//
//
size_t EntityBattleStats::GetMaxHP() const {
	return MaxHP;
}
void EntityBattleStats::SetMaxHP(size_t hp) {
	if (hp == 0)
		throw exception("Hit points count must be more than zero");

	if (CurrentHP > hp)
		CurrentHP = hp;
	MaxHP = hp;
}
size_t EntityBattleStats::GetCurrentHP() const {
	return CurrentHP;
}
void EntityBattleStats::SetCurrentHP(size_t hp) {
	if (hp == 0)
		throw exception("Hit points count must be more than zero");

	if (hp > MaxHP)
		CurrentHP = MaxHP;
	else
		CurrentHP = hp;
}
void EntityBattleStats::RestoreHealth() {
	SetCurrentHP(MaxHP);
}
//
//
//Moving
//
//
float EntityBattleStats::GetMovingSpeed() const {
	return MovingSpeed;
}
void EntityBattleStats::SetMovingSpeed(float speed){
	if (speed < 0)
		throw exception("Moving spedd cannot be less than zero.");
	
	MovingSpeed = speed;
}
//
//
//Attack
//
//
size_t EntityBattleStats::GetAADamage() const {
	return AADamage;
}
void EntityBattleStats::SetAADamage(size_t damage) {
	AADamage = damage;
}
float EntityBattleStats::GetAASpeed() const {
	return AASpeed;
}
void EntityBattleStats::SetAASpeed(float speed) {
	if (speed < 0)
		throw exception("AA speed cannot be less than zero");

	AASpeed = speed;
}
float EntityBattleStats::GetAARadius() const {
	return AARadius;
}
void EntityBattleStats::SetAARadius(float radius) {
	if (radius < 0)
		throw exception("AA radius cannot be less than zero");

	AARadius = radius;
}