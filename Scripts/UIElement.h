#pragma once

#include <TransformableObj.h>
#include <ICallbackRec_GraphPostRen.h>

using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::Core;
using namespace sf;

#define DEFAULT_ANCHOR Vector2f(0,0)

namespace KrostganEngine::UI {
	class UIElement : public TransformableObj, public ICallbackRec_GraphPostRen {
	public:
		virtual ~UIElement(){}

		void SetAnchor				(Vector2f anchor);
		void SetLocalUISize			(Vector2f localSize);
		void SetGlobalUISize		(Vector2f globalSize);
		void SetLocalScaleByUISize	(Vector2f uiSize);
		void SetGlobalScaleByUISize	(Vector2f uiSize);
		
		Vector2f	GetAnchor() const;
		Vector2f	GetLocalUISize() const;
		Vector2f	GetGlobalUISize() const;
		/// <summary>
		/// Return size of UI-element's borders  in pixels
		/// </summary>
		/// <returns></returns>
		Vector2f	GetPixelSize() const;
		/// <summary>
		/// Return offset from global position of element's parent to its anchor in pixels
		/// </summary>
		/// <returns></returns>
		Vector2f			GetAnchoredOffset() const;
		/// <summary>
		/// Return global position of element, which should in this coords with given acnhor
		/// and 0;0-local position
		/// </summary>
		/// <returns></returns>
		Vector2f			GetAnchoredGlobalPos(Vector2f anchor) const;
		const Rect<float>&	GetBorders() const;

		void SetOrigin(Vector2f origin) override {}

	private:
		void ctor_initialize(Vector2f UISize);

	protected:
		/// <summary>
		/// Nullptr as the Parent means that parent of the element will be root of UI (UserInterfaceManager::GetRoot())
		/// </summary>
		/// <param name="Owner"></param>
		/// <param name="Parent"></param>
		/// <param name="GlobalPosition"></param>
		/// <param name="LocalScale"></param>
		/// <param name="Anchor"></param>
		/// <param name="UISize"></param>
		UIElement(
			Transformable&		Owner,
			UIElement*			Parent,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			LocalScale		= DEFAULT_SCALE,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Vector2f			UISize			= DEFAULT_SCALE,
			char				RendLayer		= 0);

		/// <summary>
		/// Nullptr as the Parent means that parent of the element will be root of UI (UserInterfaceManager::GetRoot())
		/// </summary>
		/// <param name="Owner"></param>
		/// <param name="Parent"></param>
		/// <param name="GlobalPosition"></param>
		/// <param name="LocalScale"></param>
		/// <param name="Anchor"></param>
		/// <param name="UISize"></param>
		UIElement(
			Transformable&		Owner,
			UIElement*			Parent,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				LocalScale		= 1,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Vector2f			UISize			= DEFAULT_SCALE,
			char				RendLayer		= 0);

		UIElement(
			Transformable&		Owner,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			GlobalScale		= DEFAULT_SCALE,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Vector2f			UISize			= DEFAULT_SCALE,
			char				RendLayer		= 0);
		
		UIElement(
			Transformable&		Owner,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				GlobalScale		= 1,
			Vector2f			Anchor			= DEFAULT_ANCHOR,
			Vector2f			UISize			= DEFAULT_SCALE,
			char				RendLayer		= 0);

		//Rewrite algorithm of local position's calculation by binding transform's center of
		//child element to anchor of parent (not to its origin)
		Vector2f	GetLocalPositionFromParent	() override;
		Vector2f	TransformLocalPosToGlobal	(Vector2f localPos) override;
			
		void		ScaleObject					(Vector2f scale) override;

		void		SetScale_Inherit			() override;

		virtual	void SetUISize_Inherit();
		virtual void SetChildren_UISize();

		Vector2f		Anchor		= Vector2f(0,0);
		Rect<float>		Borders;
	};
}