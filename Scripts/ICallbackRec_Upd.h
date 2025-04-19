#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine {
	namespace GameObjects {

		struct CallbackRecArgs_Upd {
			CallbackRecArgs_Upd(RenderWindow& Window, Event& UpdateEvent);
			RenderWindow& Window;
			Event& UpdateEvent;
		};

		class ICallbackRec_Upd {
		public:
			virtual void Update(CallbackRecArgs_Upd args) = 0;
		protected:
			ICallbackRec_Upd() {};
		};
	}
}