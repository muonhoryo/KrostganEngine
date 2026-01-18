
#include <EntityOrder_ImmobilityChecking.h>
#include <Engine.h>
#include <VectExts.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

bool EntityOrder_ImmobilityChecking::CheckImmobility(Vector2f target) const{
	return CheckImmobility(SquareLength(target - Owner.GetGlobalPosition()));
}
bool EntityOrder_ImmobilityChecking::CheckImmobility(float toTargetDist_sqr) const{

	bool immobile = false;

	if (abs(toTargetDist_sqr - PrevToTargetDist_Sqr) <= Engine::GetGlobalConsts().Units_ImmobilityCheckValue)
		immobile = true;

	PrevToTargetDist_Sqr = toTargetDist_sqr;
	return immobile;
}
