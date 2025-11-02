
#include <AutoAttackStats.h>
#include <iostream>

using namespace std;
using namespace KrostganEngine::GameObjects;

AutoAttackStats::AutoAttackStats() {

	//size_t
	InitializeField_s_t(AAStatType::AADamage, 0);

	//float
	InitializeField_f(AAStatType::AASpeed, 0);
	InitializeField_f(AAStatType::AARange, 0);

	//bool
	InitializeField_bool(AAStatType::IsRange, false);
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