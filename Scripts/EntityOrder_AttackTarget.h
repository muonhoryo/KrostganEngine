#pragma once

#include <Entity.h>
#include <EntityOrder_ObjectTarget.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_AttackTarget:public IEntityOrder,public EntityOrder_ObjectTarget {
	public:
		EntityOrder_AttackTarget(Entity& Owner, IAttackableObj& Target);

		bool CheckExecCondition() override;
		list<IEntityAction*>& GetActions() override;
		void OnStartExecution() override;
		void OnEndExecution() override;
		EntityOrderType GetOrderType() override;

		const TransformableObj& GetTarget() const override;

		Entity& Owner;
		AutoAttackModule& AAModule;
		IAttackableObj& Target;
	};
}