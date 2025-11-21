#pragma once

#include <OrdersExecutor.h>
#include <watch_ptr.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_AutoAttack:public IEntityAction {
	public:
		EntityAction_AutoAttack(OrdersExecutor& Owner, watch_ptr_handler_wr<IAttackableObj> Target);

		bool CheckExecCondition() override;
		void Execute() override;

	private:
		OrdersExecutor& Owner;
		watch_ptr_handler_wr<IAttackableObj> Target;
		
		//Cashed
		//IHitPointModule& TargetHPModule;
		AutoAttackModule& AAModule;
	};
}