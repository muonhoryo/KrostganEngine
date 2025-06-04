#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::Core {
	struct CallbackRecArgs_LUpd {
	};

	class ICallbackRec_LUpd {
	public:
		virtual ~ICallbackRec_LUpd();

		virtual void Update(CallbackRecArgs_LUpd args) = 0;
	protected:
		ICallbackRec_LUpd();
	};
}