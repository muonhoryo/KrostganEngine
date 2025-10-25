#pragma once

#include <SFML/Graphics.hpp>
#include <watch_ptr.h>

#define DEFAULT_RENDLAYER (byte)0
#define DEFAULT_RENDLAYER_UI (byte)25

using namespace sf;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	class ICallbackRec_GraphRen : public virtual w_ptr_observable {

	public:
		void RenderGraphic(RenderWindow& window);
		virtual ~ICallbackRec_GraphRen();

		byte			GetRendLayer() const;
		virtual bool	GetActivity() const;

		void SetRendLayer(byte layer);
		void SetActivity(bool isActive);

	protected:
		ICallbackRec_GraphRen(byte RendLayer = DEFAULT_RENDLAYER);

		virtual void RenderGraphicAction(RenderWindow& window) = 0;

		byte RendLayer;
		bool IsActive = true;
	};
}