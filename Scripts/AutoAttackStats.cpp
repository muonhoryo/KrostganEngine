
#include <AutoAttackStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

AutoAttackStats::AutoAttackStats(const LvlObjInstantiationInfo* ProjectileInfo)
	:ProjectileInfo(ProjectileInfo==nullptr? LvlObjInstantiationInfo() : *ProjectileInfo){

	//size_t
	InitializeField_s_t(AAStatType::AADamage, 0);

	//float
	InitializeField_f(AAStatType::AASpeed, 0);
	InitializeField_f(AAStatType::AARange, 0);
	InitializeField_f(AAStatType::AAProjSpeed, 0);

	//bool
	InitializeField_bool(AAStatType::IsRange, false);
	InitializeField_bool(AAStatType::Proj_LockRotation, false);
}
void AutoAttackStats::CopyTo(ModifiableStatsWrapper
	<AutoAttackStats_Consts::StatType,
	AutoAttackStats_Consts::FIELDS_COUNT,
	AutoAttackStats_Consts::StatTypeNames,
	AutoAttackStats_Consts::FIELDS_COUNT_F,
	AutoAttackStats_Consts::FIELDS_COUNT_S_T,
	AutoAttackStats_Consts::FIELDS_COUNT_BOOL>& toCopy) const {

	ModifiableStatsWrapper::CopyTo(toCopy);
	AutoAttackStats* parCopy = dynamic_cast<AutoAttackStats*>(&toCopy);
	CopyTo_Internal(*parCopy);
}
void AutoAttackStats::CopyTo_Internal(AutoAttackStats& toCopy) const {
	toCopy.SetProjectileInfo(ProjectileInfo);
}

void AutoAttackStats::SetAADamage(size_t damage) {
	SetDefaultStat(AAStatType::AADamage, damage);
}
void AutoAttackStats::SetAASpeed(float speed) {
	if (speed < 0)
		throw exception("AA speed cannot be less than zero");

	SetDefaultStat(AAStatType::AASpeed, speed);
}
void AutoAttackStats::SetAARange(float range) {
	if (range < 0)
		throw exception("AA range cannot be less than zero");

	SetDefaultStat(AAStatType::AARange, range);
}
void AutoAttackStats::SetIsRange(bool isRange) {

	SetDefaultStat(AAStatType::IsRange,isRange);
}
void AutoAttackStats::SetProjectileInfo(const LvlObjInstantiationInfo& projInfo) {
	ProjectileInfo = projInfo;
}
void AutoAttackStats::SetAAProjSpeed(float speed) {

	SetDefaultStat(AAStatType::AAProjSpeed, speed);
}
void AutoAttackStats::SetProjLockRotation(bool lockRotation) {

	SetDefaultStat(AAStatType::Proj_LockRotation, lockRotation);
}