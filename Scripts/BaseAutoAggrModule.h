#pragma once

#include <OrdersExecutor.h>
#include <Physics.h>
#include <RelationsSystem.h>
#include <Entity.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Physics;

namespace KrostganEngine::GameObjects {
	class BaseAutoAggrModule : public AutoAggressionModule {
	public:
		BaseAutoAggrModule(Entity& Owner, ExecutorActionsMediator& ActionMediator);
		~BaseAutoAggrModule();

		void TurnOnAction() override;
		void TurnOffAction() override;

		void UpdateAction(CallbackRecArgs_Upd& args) override;

		IAttackableObj& GetCurrTarget() const;

	private:
		void CheckCurrTarget(CallbackRecArgs_Upd& args);
		void FindTarget(CallbackRecArgs_Upd& args);
		void TurnFindTargetState();

		IAttackableObj* Target;
		TransformableObj* TargetTransform;
		Entity& Owner;

		bool HasTarget;
		bool IsAttack;

		vector<IPhysicalObject*> TargsBuffer;

		static inline const PhysicsLayer TARGETS_MASK = (PhysicsLayer)((int)PhysicsLayer::Buildings | (int)PhysicsLayer::Units);
	};
}