#pragma once

#include <SFML/Graphics.hpp>
#include <watch_ptr.h>

using namespace sf;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	struct CallbackRecArgs_LUpd {
	};

	class ICallbackRec_LUpd : public virtual w_ptr_observable{
	
	public:
		virtual ~ICallbackRec_LUpd();

		virtual void Update(CallbackRecArgs_LUpd args) = 0;

	protected:
		ICallbackRec_LUpd();

	};
}