
#include <EntityBattleStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

EntityBattleStats::~EntityBattleStats() {
	for (auto mod : ParamModifiers) {
		delete mod;
	}
}

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

//
//
// Field's getting
//
//

EntityBattleStats::StatType		EntityBattleStats::GetFieldType(EntityBattleStats::StatType type) {
	return (EntityBattleStats::StatType)((int)type & (int)EntityBattleStats::StatType::type_mask);
}
const size_t* EntityBattleStats::GetFieldRef_s_t(EntityBattleStats::StatType type, bool isDefField) const {
	
	auto param = GetParameterByType_s_t(type);
	if (param == nullptr)
		return nullptr;
	else
		return &GetFieldRefFromParameter(*param, isDefField);
}
const float* EntityBattleStats::GetFieldRef_f(EntityBattleStats::StatType type,bool isDefField) const {

	auto param = GetParameterByType_f(type);
	if (param == nullptr)
		return nullptr;
	else
		return &GetFieldRefFromParameter(*param, isDefField);
}
const void* EntityBattleStats::GetFieldRef(StatType type, bool isDefField) const {

	StatType fieldType = GetFieldType(type);
	switch (fieldType) {
	case StatType::t_size_t:
		return GetFieldRef_s_t(type, isDefField);
	case StatType::t_float:
		return GetFieldRef_f(type, isDefField);
	default:
		return nullptr;
	}
}
const EntityBattleStats::Parameter<size_t>* EntityBattleStats::GetParameterByType_s_t(StatType type) const {

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
const EntityBattleStats::Parameter<float>* EntityBattleStats::GetParameterByType_f(StatType type) const {

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

//
//
// Parameter's modifiers
//
//

void EntityBattleStats::RecalculateStat(StatType type) {

	StatType fieldType = GetFieldType(type);

	switch (fieldType) {
		case StatType::t_size_t:
			RecalculateStat_t<size_t>(type, *GetParameterByType_s_t(type));
			break;
		case StatType::t_float:
			RecalculateStat_t<float>(type, *GetParameterByType_f(type));
			break;
		default:
			cout << "Missing type of field" << endl;
			throw exception("Cant recalculate field");
			return;
	}
	StatChangedEventHan.Execute(type);
}

void EntityBattleStats::AddModifier(const ParamModifier & mod) {
	if (StatToStr(mod.FieldType) == "")
		throw exception("Missing field type");

	CollectionsExts::InsertSorted(ParamModifiers, &mod, ParamModsSortFuncInstance);
	RecalculateStat(mod.FieldType);
}
void EntityBattleStats::RemoveModifier(const ParamModifier& mod) {
	CollectionsExts::Remove(ParamModifiers, &mod);
	RecalculateStat(mod.FieldType);
}

//
//
// Set default stat's fields
//
//

//
// 
//HitPoint
//
//
void EntityBattleStats::SetMaxHP(size_t hp) {
	if (hp == 0)
		throw exception("Hit points count must be more than zero");

	SetDefaultStat(StatType::MaxHP, MaxHP, hp);
}
void EntityBattleStats::SetHPRegenAmount(size_t amount) {

	SetDefaultStat(StatType::RegenHP_Amount, RegenHP_Amount, amount);
}
void EntityBattleStats::SetHPRegenTick(float tick) {
	if (tick <= 0) {
		return;
	}

	SetDefaultStat(StatType::RegenHP_Tick, RegenHP_Tick, tick);
}
//
//
//Moving
//
//
void EntityBattleStats::SetMovingSpeed(float speed) {
	if (speed < 0)
		throw exception("Moving spedd cannot be less than zero.");

	SetDefaultStat(StatType::MovingSpeed, MovingSpeed, speed);
}
//
//
//Attack
//
//
void EntityBattleStats::SetAADamage(size_t damage) {
	SetDefaultStat(StatType::AADamage, AADamage, damage);
}
void EntityBattleStats::SetAASpeed(float speed) {
	if (speed < 0)
		throw exception("AA speed cannot be less than zero");

	SetDefaultStat(StatType::AASpeed, AASpeed, speed);
}
void EntityBattleStats::SetAARange(float range) {
	if (range < 0)
		throw exception("AA range cannot be less than zero");

	SetDefaultStat(StatType::AARange, AARange, range);
}
//
// 
// View
// 
//
void EntityBattleStats::SetAutoAggrRadius(float radius) {
	if (radius < 0)
		throw exception("AutoAggression radius cannot be less than zero");

	SetDefaultStat(StatType::AutoAggrRadius, AutoAggrRadius, radius);
}