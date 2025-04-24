#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine {
	namespace GameObjects {
		class ICallbackRec_GraphRen {
		public:
			virtual void RenderGraphic(RenderWindow& window)=0;
			~ICallbackRec_GraphRen();
		protected:
			ICallbackRec_GraphRen();
		};
	}
}