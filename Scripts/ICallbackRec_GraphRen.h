#pragma once

#include <SFML/Graphics.hpp>
#include <ICallbackRec.h>

#define DEFAULT_RENDLAYER (std::byte)20
#define DEFAULT_RENDLAYER_UI (std::byte)128

using namespace sf;
using namespace KrostganEngine;
using namespace std;

namespace KrostganEngine::Core {
	class ICallbackRec_GraphRen : public virtual ICallbackRec{

	public:
		void RenderGraphic(RenderWindow& window);
		virtual ~ICallbackRec_GraphRen();

		std::byte		GetRendLayer() const;
		/// <summary>
		/// Define that object-inheritor is hide by war fog on render or not. If false object always renders while placed on window.
		/// </summary>
		bool			Get_IsHidenByWarFog() const;
		/// <summary>
		/// Define object-inheritor is shown by war fog on render or not. If true the render module ignores parameter IsHidenWarFog and render only when
		/// object is covered by war fog.
		/// </summary>
		bool			Get_IsShownByWarFog() const;
		virtual bool	GetActivity() const;

		void SetRendLayer(std::byte layer);
		void SetActivity(bool isActive);
		void Set_IsHidenByWarFog(bool isHiden);
		void Set_IsShownByWarFog(bool isShown);

	protected:
		ICallbackRec_GraphRen(std::byte RendLayer = DEFAULT_RENDLAYER);

		virtual void RenderGraphicAction(RenderWindow& window) = 0;

		std::byte RendLayer;
		bool IsActive = true;

		/// <summary>
		/// Define that object-inheritor is hide by war fog on render or not. If false object always renders while placed on window.
		/// </summary>
		bool IsHidenByWarFog = false;
		/// <summary>
		/// Define object-inheritor is shown by war fog on render or not. If true the render module ignores parameter IsHidenWarFog and render only when
		/// object is covered by war fog.
		/// </summary>
		bool IsShownByWarFog = false;
	};
}