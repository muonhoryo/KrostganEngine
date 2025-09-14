
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

void EntityBattleStats::CopyTo(EntityBattleStats& tocopy) const {

	//IT SHOULD BE OVERRIDING WITH MEMORY CONTROL
	//!!!!!!!!!!!
	tocopy.MaxHP =MaxHP;
	tocopy.RegenHP_Amount =RegenHP_Amount;		
	tocopy.RegenHP_Tick=RegenHP_Tick;
	tocopy.MovingSpeed =MovingSpeed;
	tocopy.AADamage = AADamage;
	tocopy.AASpeed = AASpeed;
	tocopy.AARange = AARange;
	tocopy.AutoAggrRadius = AutoAggrRadius;
}

EntityBattleStats::StatType		EntityBattleStats::GetFieldType(EntityBattleStats::StatType type) {
	return (EntityBattleStats::StatType)((int)type & (int)EntityBattleStats::StatType::type_mask);
}
const size_t* EntityBattleStats::GetFieldRef_s_t(EntityBattleStats::StatType type) const {

	if (GetFieldType(type) != EntityBattleStats::StatType::t_size_t)
		return nullptr;
	
	switch (type)
	{
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::MaxHP:
		return &MaxHP;
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::RegenHP_Amount:
		return &RegenHP_Amount;
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::AADamage:
		return &AADamage;
	default:
		return nullptr;
	}
}
const float* EntityBattleStats::GetFieldRef_f(EntityBattleStats::StatType type) const {

	if (GetFieldType(type) != EntityBattleStats::StatType::t_float)
		return nullptr;

	switch (type)
	{
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::RegenHP_Tick:
		return &RegenHP_Tick;
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::MovingSpeed:
		return &MovingSpeed;
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::AASpeed:
		return &AASpeed;
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::AARange:
		return &AARange;
	case KrostganEngine::GameObjects::EntityBattleStats::StatType::AutoAggrRadius:
		return &AutoAggrRadius;
	default:
		return nullptr;
	}
}
const void* EntityBattleStats::GetFieldRef(StatType type) const {
	const void* ref = GetFieldRef_s_t(type);
	if (ref != nullptr)
		return ref;

	ref = GetFieldRef_f(type);
	if (ref != nullptr)
		return ref;

	return ref;
}
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

	AARange = radius;

	StatChangedEventHan.Execute(StatType::AARange);
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