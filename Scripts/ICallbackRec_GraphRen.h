#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::Core {
	class ICallbackRec_GraphRen {
	public:
		virtual void RenderGraphic(RenderWindow& window) = 0;
		virtual ~ICallbackRec_GraphRen();
	protected:
		ICallbackRec_GraphRen();
	};
}