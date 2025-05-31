#pragma once

#include <ICallbackRec_Upd.h>
#include <Physics.h>
#include <HPSystem.h>
#include <SFML/System.hpp>

using namespace sf;
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

		static bool GivingOrderCondition();

		static void GiveOrderToSelected_MoveToPoint(Vector2f targetGlobalPos,bool isGrouped);
		static void GiveOrderToSelected_AttackTarget(IAttackableObj& target,bool isGrouped);
		static void GiveOrderToSelected_Idle(bool isGrouped);
		static void GiveOrderToSelected_Cancel();
		static void GiveOrderToSelected_HoldPosition(bool isGrouped);
	};

	class EntitiesCtrlInputHandler :public ICallbackRec_Upd {
	public:
		EntitiesCtrlInputHandler();
		EntitiesCtrlInputHandler(EntitiesCtrlInputMode* CurrMode);

		void SetNewMode(EntitiesCtrlInputMode& newMode);

		bool GetShiftPresState();

		/// <summary>
		/// Return true if state of order's grouping was changed
		/// </summary>
		/// <param name="ev"></param>
		/// <returns></returns>
		bool HandleShiftInput(const Event& ev);

		void Update(CallbackRecArgs_Upd args) override;

	private:
		EntitiesCtrlInputMode* CurrMode;

		bool IsShiftPressed = false;
	};
}