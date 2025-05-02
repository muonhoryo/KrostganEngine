#pragma once

#include <ICallbackRec_Upd.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::PlayerControl {
	class OrdersSystemInteraction:public ICallbackRec_Upd {
	public:
		OrdersSystemInteraction();
		void Update(CallbackRecArgs_Upd args) override;

	private:
		static void GiveOrderToSelected_MoveToPoint();
	};
}
