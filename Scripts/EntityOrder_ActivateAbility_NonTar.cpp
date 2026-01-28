
#include <EntityOrder_ActivateAbility_NonTar.h>
#include <_AbilitiesSystem.h>

using namespace KrostganEngine::EntitiesControl;

EntityOrder_ActivateAbility_NonTar::EntityOrder_ActivateAbility_NonTar(OrdersExecutor& Owner, size_t AbilityIndex)
	:Owner(Owner), AbilityIndex(AbilityIndex){

}

void EntityOrder_ActivateAbility_NonTar::OnStartExecution() {

	HasExecuted = true;

	auto ability = Owner.GetAbility(AbilityIndex);
	if (ability == nullptr)
		return;

	auto ability_nonTarget = dynamic_cast<Ability_NonTargetable*>(ability);
	if (ability_nonTarget != nullptr) {
		ability_nonTarget->Activate();
	}
}
EntityOrderType EntityOrder_ActivateAbility_NonTar::GetOrderType() {
	return EntityOrderType::AbilityUsing;
}