#pragma once

#include <watch_ptr.h>

using namespace KrostganEngine;

namespace KrostganEngine::Core {
	class ICallbackRec : public virtual w_ptr_observable {
	public:
		virtual ~ICallbackRec(){}

		bool IsDestroyedOnUnload() const { return DestroyOnUnload; }

	protected:
		ICallbackRec(){}

		bool DestroyOnUnload = true;
	};
}