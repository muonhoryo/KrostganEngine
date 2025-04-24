#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

using namespace sf;
using namespace std;

namespace KrostganEngine {
	namespace GameObjects {

		struct CallbackRecArgs_Upd {
			CallbackRecArgs_Upd(const vector<Event>& playerInput);
			const vector<Event>& PlayerInput;
		};

		class ICallbackRec_Upd {
		public:
			virtual void Update(CallbackRecArgs_Upd args) = 0;
			~ICallbackRec_Upd();
		protected:
			ICallbackRec_Upd();
		};
	}
}