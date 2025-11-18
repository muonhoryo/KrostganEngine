
#include <AutoAttackStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

AutoAttackStats::AutoAttackStats
	(const LvlObjInstantiationInfo* ProjectileInfo,
	const LvlObjInstantiationInfo* SiegeHitEffInfo)
		:ProjectileInfo(ProjectileInfo==nullptr? LvlObjInstantiationInfo() : *ProjectileInfo),
		SiegeHitEffInfo(SiegeHitEffInfo==nullptr? LvlObjInstantiationInfo(): *SiegeHitEffInfo){

	//size_t
	InitializeField_s_t(AAStatType::Damage, 0);

	//float
	InitializeField_f(AAStatType::Speed, 0);
	InitializeField_f(AAStatType::Range, 0);
	InitializeField_f(AAStatType::ProjSpeed, 0);
	InitializeField_f(AAStatType::SiegeRange, 1);

	//bool
	InitializeField_bool(AAStatType::IsRange, false);
	InitializeField_bool(AAStatType::IsSiege, false);
	InitializeField_bool(AAStatType::Proj_LockRotation, false);
	InitializeField_bool(AAStatType::Proj_IsSelfHoming, true);
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
	toCopy.SetSiegeHitEffInfo(SiegeHitEffInfo);
}

void AutoAttackStats::SetDamage(size_t damage) {
	SetDefaultStat(AAStatType::Damage, damage);
}
void AutoAttackStats::SetSpeed(float speed) {
	if (speed < 0)
		throw exception("AA speed cannot be less than zero");

	SetDefaultStat(AAStatType::Speed, speed);
}
void AutoAttackStats::SetRange(float range) {
	if (range < 0)
		throw exception("AA range cannot be less than zero");

	SetDefaultStat(AAStatType::Range, range);
}
void AutoAttackStats::SetIsRange(bool isRange) {

	SetDefaultStat(AAStatType::IsRange,isRange);
}
void AutoAttackStats::SetProjSpeed(float speed) {

	SetDefaultStat(AAStatType::ProjSpeed, speed);
}
void AutoAttackStats::SetSiegeRange(float range) {

	SetDefaultStat(AAStatType::SiegeRange, range);
}
void AutoAttackStats::SetIsSiege(bool isSiege) {

	SetDefaultStat(AAStatType::IsSiege, isSiege);
}
void AutoAttackStats::SetProj_LockRotation(bool lockRotation) {

	SetDefaultStat(AAStatType::Proj_LockRotation, lockRotation);
}
void AutoAttackStats::SetProj_IsSelfHoming(bool isSelfHoming) {

	SetDefaultStat(AAStatType::Proj_IsSelfHoming, isSelfHoming);
}

void AutoAttackStats::SetProjectileInfo(const LvlObjInstantiationInfo& projInfo) {
	ProjectileInfo = projInfo;
}
void AutoAttackStats::SetSiegeHitEffInfo(const LvlObjInstantiationInfo& siegeEffInho) {
	SiegeHitEffInfo = siegeEffInho;
}