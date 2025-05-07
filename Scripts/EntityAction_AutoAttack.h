#pragma once

#include <Entity.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityAction_AutoAttack:public IEntityAction {
	public:
		EntityAction_AutoAttack(Entity& Owner,IAttackableObj& Target);

		bool CheckExecCondition() override;
		void Execute() override;

	private:
		Entity& Owner;
		IAttackableObj& Target;
		IHitPointModule& TargetHPModule;
		AutoAttackModule& AAModule;
	};
}