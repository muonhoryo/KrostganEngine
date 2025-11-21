
#include <IAttackableObj.h>

using namespace KrostganEngine::GameObjects;

bool IAttackableObj::CheckAttackReachability(IAttackableObj::AtkParam atkParam) const{

	bool isAA = ((short)atkParam & (short)AtkParam::IsAA) != 0;

	if (isAA && !IsTargetableForAA())
		return false;

	if (GetHPModule().DeathModule.GetIsDeadState())
		return false;

	return true;
}