#pragma once

#include <SFML/Graphics.hpp>
#include <watch_ptr.h>

using namespace sf;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	class ICallbackRec_GraphPostRen : public virtual w_ptr_observable{

	public:
		void RenderGraphic(RenderWindow& window);
		virtual ~ICallbackRec_GraphPostRen();

		char GetRendLayer() const;
		bool GetActivity() const;

		void SetRendLayer(char layer);
		void SetActivity(bool isActive);

	protected:
		ICallbackRec_GraphPostRen(char RendLayer = 0);

		virtual void RenderGraphicAction(RenderWindow& window) = 0;

	private:
		char RendLayer	= 0;
		bool IsActive	= true;
	};
}