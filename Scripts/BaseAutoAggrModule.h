#pragma once

#include <OrdersExecutor.h>
#include <Physics.h>
#include <RelationsSystem.h>
#include <Entity.h>
#include <watch_ptr.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine;

namespace KrostganEngine::GameObjects {
	class BaseAutoAggrModule : public AutoAggressionModule {
	public:
		BaseAutoAggrModule(Entity& Owner, ExecutorActionsMediator& ActionMediator);
		~BaseAutoAggrModule();

		void TurnOnAction() override;
		void TurnOffAction() override;

		void UpdateAction(CallbackRecArgs_Upd& args) override;

		IAttackableObj* GetCurrTarget() const;

	private:
		void CheckCurrTarget(CallbackRecArgs_Upd& args);
		void FindTarget(CallbackRecArgs_Upd& args);
		void TurnFindTargetState();

		/// <summary>
		/// Return false if target cannot be reached
		/// </summary>
		/// <returns></returns>
		bool CheckTargetReachability() const;

		watch_ptr_handler_wr<IAttackableObj>* Target;
		WorldTransfObj* TargetTransform;
		Entity& Owner;

		bool HasTarget;
		bool IsAttack;

		vector<IPhysicalObject*> TargsBuffer;

		static inline const PhysicsLayer TARGETS_MASK = (PhysicsLayer)((int)PhysicsLayer::Buildings | (int)PhysicsLayer::Units);
	};
}