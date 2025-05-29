#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

namespace KrostganEngine::Core {
	struct CallbackRecArgs_Upd {
		CallbackRecArgs_Upd(const vector<Event>& PlayerInput,float LastFrameDeltaTime);
		const vector<Event>& PlayerInput;
		float LastFrameDeltaTime; //Milliseconds
	};

	class ICallbackRec_Upd {
	public:
		virtual void Update(CallbackRecArgs_Upd args) = 0;
		virtual ~ICallbackRec_Upd();
	protected:
		ICallbackRec_Upd();
	};
}