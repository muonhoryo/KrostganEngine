#pragma once

#include <SFML/Graphics.hpp>
#include <ICallbackRec.h>

using namespace sf;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	struct CallbackRecArgs_LUpd {
	};

	class ICallbackRec_LUpd : public virtual ICallbackRec {
	
	public:
		virtual ~ICallbackRec_LUpd();

		virtual void Update(CallbackRecArgs_LUpd args) = 0;

	protected:
		ICallbackRec_LUpd();

	};
}