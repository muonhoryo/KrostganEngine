#pragma once

#include <SFML/Graphics.hpp>
#include <watch_ptr.h>

using namespace sf;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	class ICallbackRec_GraphPostRen : public virtual w_ptr_observable{

	public:
		virtual void RenderGraphic(RenderWindow& window) = 0;
		virtual ~ICallbackRec_GraphPostRen();

		char GetRendLayer() const;
		void SetRendLayer(char layer);

	protected:
		ICallbackRec_GraphPostRen(char RendLayer = 0);

	private:
		char RendLayer = 0;

	};
}