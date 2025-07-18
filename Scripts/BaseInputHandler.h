#pragma once

#include <ICallbackRec_Upd.h>
#include <SFML/System.hpp>

using namespace KrostganEngine::Core;
using namespace sf;

namespace KrostganEngine::PlayerControl {
	class BaseInputHandler :public ICallbackRec_Upd {
	public:
		BaseInputHandler();
		void Update(CallbackRecArgs_Upd args) override;
	};
}


