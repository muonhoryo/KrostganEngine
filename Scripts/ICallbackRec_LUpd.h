#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine {
	namespace GameObjects {

		struct CallbackRecArgs_LUpd {
		};

		class ICallbackRec_LUpd {
		public:
			virtual void Update(CallbackRecArgs_LUpd args) = 0;
		protected:
			ICallbackRec_LUpd() {};
		};
	}
}