#pragma once

#include <OrdersExecutor.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_AutoAttack:public IEntityAction {
	public:
		EntityAction_AutoAttack(OrdersExecutor& Owner,IAttackableObj& Target);

		bool CheckExecCondition() override;
		void Execute() override;

	private:
		OrdersExecutor& Owner;
		IAttackableObj& Target;
		
		//Cashed
		IHitPointModule& TargetHPModule;
		AutoAttackModule& AAModule;
	};
}