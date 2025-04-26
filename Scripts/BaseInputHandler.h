#pragma once
#include <EngineCore.h>

namespace KrostganEngine::PlayerControl {
	class BaseInputHandler :public ICallbackRec_Upd {
	public:
		BaseInputHandler();
		void Update(CallbackRecArgs_Upd args) override;
	};
}


