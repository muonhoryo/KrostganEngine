#pragma once

#include <HierarchyTrObj.h>
#include <ICallbackRec_GraphPostRen.h>

using namespace KrostganEngine::Core;
using namespace sf;

#define DEFAULT_ANCHOR Vector2f(0,0)

namespace KrostganEngine::UI {

	class UIElement;

	class UIElement : public HierarchyTrObj, public virtual ICallbackRec_GraphPostRen {
	public:
		virtual ~UIElement(){}

		//
		//
		//TransformableObj
		//
		//

		Vector2f			GetLocalPosition() const override;
		Vector2f			GetLocalScale() const override;

		void SetGlobalPosition(Vector2f position) override;
		void SetLocalPosition(Vector2f position) override;
		void SetGlobalScale(Vector2f scale) override;
		void SetLocalScale(Vector2f scale) override;
		void SetOrigin(Vector2f origin) override;

		//
		//
		//IHierarchyTrObj
		//
		//

		void	SetParent(IHierarchyTrObj* parent) override;

		//
		//
		// UI
		//
		//

		void SetAnchor				(Vector2f anchor);
		void SetLocalUISize			(Vector2f localSize);
		void SetGlobalUISize		(Vector2f globalSize);
		void SetLocalScaleByUISize	(Vector2f uiSize);
		void SetGlobalScaleByUISize	(Vector2f uiSize);
		void SetResizingUIByInherit	(bool resizeByInherit);

		Vector2f			GetAnchor() const;
		Vector2f			GetLocalUISize() const;
		Vector2f			GetGlobalUISize() const;
		/// <summary>
		/// Return size of UI-element's borders  in pixels
		/// </summary>
		/// <returns></returns>
		Vector2f			GetPixelSize() const;
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
		bool				GetResizingUIByInherit() const;

		bool		GetInheritActivity() const;
		bool		GetSelfActivity() const;
		bool		GetActivity() const override;

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
			Vector2f			LocalPosition = DEFAULT_POSITION,
			Vector2f			LocalScale = DEFAULT_SCALE,
			Vector2f			Anchor = DEFAULT_ANCHOR,
			Vector2f			UISize = DEFAULT_SCALE);

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
			Vector2f			LocalPosition = DEFAULT_POSITION,
			float				LocalScale = 1,
			Vector2f			Anchor = DEFAULT_ANCHOR,
			Vector2f			UISize = DEFAULT_SCALE);

		UIElement(
			Transformable&		Owner,
			Vector2f			GlobalPosition = DEFAULT_POSITION,
			Vector2f			GlobalScale = DEFAULT_SCALE,
			Vector2f			Anchor = DEFAULT_ANCHOR,
			Vector2f			UISize = DEFAULT_SCALE);

		UIElement(
			Transformable&		Owner,
			Vector2f			GlobalPosition = DEFAULT_POSITION,
			float				GlobalScale = 1,
			Vector2f			Anchor = DEFAULT_ANCHOR,
			Vector2f			UISize = DEFAULT_SCALE);

		virtual	void SetUISize_Inherit(Vector2f oldSize);
		virtual void SetChildren_UISize(Vector2f oldSize);

		Vector2f		Anchor = Vector2f(0, 0);
		Rect<float>		Borders;

	private:
		void ctor_initialize(Vector2f UISize);

		//
		//
		//Internal funcs
		//
		//

		/// <summary>
		/// Calculate local position of element from parent's transform
		/// </summary>
		/// <returns></returns>
		Vector2f	GetLocalPositionFromParent();
		Vector2f	GetLocalScaleFromParent();
		Vector2f	TransformLocalPosToGlobal(Vector2f localPos);

		/// <summary>
		/// Scale object itself by scale-param
		/// </summary>
		/// <param name="scale"></param>
		void	ScaleElement(Vector2f scale);

		void SetPosition_Inherit();
		void SetScale_Inherit();

		Vector2f	LocalPosition = DEFAULT_POSITION;
		Vector2f	LocalScale = DEFAULT_SCALE;

		bool ResizeUIByInherits = false;
	};
}