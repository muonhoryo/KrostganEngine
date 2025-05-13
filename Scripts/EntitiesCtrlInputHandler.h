#pragma once

#include <ICallbackRec_Upd.h>
#include <Physics.h>
#include <HPSystem.h>

using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::PlayerControl {
	class EntitiesCtrlInputHandler;

	class EntitiesCtrlInputMode {
	public:
		virtual ~EntitiesCtrlInputMode(){}

		virtual void HandleInput(CallbackRecArgs_Upd& args) = 0;

	protected:
		EntitiesCtrlInputMode(EntitiesCtrlInputHandler& Owner);

		EntitiesCtrlInputHandler& Owner;

		static Vector2f GetPosByCursor();
		static bool TryGetTargetAtPos(Vector2f pos, IPhysicalObject*& target);

		template<typename TTargetType>
		static bool TryGetTargetByTypeAtPos(Vector2f pos, TTargetType*& target) {
			IPhysicalObject* physTar=nullptr;
			if (!TryGetTargetAtPos(pos, physTar))
				return false;
			else {
				target = dynamic_cast<TTargetType*>(physTar);
				return target != nullptr;
			}
		}

		static void GiveOrderToSelected_MoveToPoint(Vector2f targetGlobalPos);
		static void GiveOrderToSelected_AttackTarget(IAttackableObj& target);
	};

	class EntitiesCtrlInputHandler :public ICallbackRec_Upd {
	public:
		EntitiesCtrlInputHandler();
		EntitiesCtrlInputHandler(EntitiesCtrlInputMode* CurrMode);

		void SetNewMode(EntitiesCtrlInputMode& newMode);

		void Update(CallbackRecArgs_Upd args) override;

	private:
		EntitiesCtrlInputMode* CurrMode;
	};
}