#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::Core {
	class ICallbackRec_GraphPostRen {
	public:
		virtual void RenderGraphic(RenderWindow& window) = 0;
		virtual ~ICallbackRec_GraphPostRen();
	protected:
		ICallbackRec_GraphPostRen();
	};
}