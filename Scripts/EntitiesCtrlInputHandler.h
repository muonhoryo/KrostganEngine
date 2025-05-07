#pragma once

#include <ICallbackRec_Upd.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::PlayerControl {
	class EntitiesCtrlInputHandler;

	class EntitiesCtrlInputMode {
	public:
		virtual ~EntitiesCtrlInputMode(){}

		virtual void HandleInput(CallbackRecArgs_Upd& args) = 0;

	protected:
		EntitiesCtrlInputMode(EntitiesCtrlInputHandler& Owner);

		EntitiesCtrlInputHandler& Owner;

		static void GiveOrderToSelected_MoveToPoint();
		static void GiveOrderToSelected_AttackTarget();
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