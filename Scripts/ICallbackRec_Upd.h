#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <ICallbackRec.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	struct CallbackRecArgs_Upd {
		CallbackRecArgs_Upd(const vector<Event>& PlayerInput,float LastFrameDeltaTime);
		const vector<Event>& PlayerInput;
		float LastFrameDeltaTime; //Milliseconds
	};

	class ICallbackRec_Upd : public virtual ICallbackRec {
	
	public:
		virtual void Update(CallbackRecArgs_Upd args) = 0;
		
		virtual ~ICallbackRec_Upd();

	protected:
		ICallbackRec_Upd();

	};
}