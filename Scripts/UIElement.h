#pragma once

#include <HierarchyTrObj.h>
#include <ICallbackRec_GraphRen.h>

using namespace KrostganEngine::Core;
using namespace sf;

#define DEFAULT_ANCHOR Vector2f(0,0)

namespace KrostganEngine::UI {

	class UIElement;

	class UIElement : public HierarchyTrObj, public ICallbackRec_GraphRen {
	public:
		virtual ~UIElement(){}

		//
		//
		//TransformableObj
		//
		//

		Vector2f			GetLocalPosition() const override;
		Vector2f			GetLocalScale() const override;
		float				GetLocalRotation() const override;

		void SetGlobalPosition(Vector2f position) override;
		void SetLocalPosition(Vector2f position) override;

		void SetGlobalScale(Vector2f scale) override;
		void SetLocalScale(Vector2f scale) override;

		void SetGlobalRotation(float rotation) override;
		void SetLocalRotation(float rotationn) override;

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
		const Vector2f&		GetGlobalUISize() const;
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
		bool				GetResizingUIByInherit() const;
		const string&		GetName() const;
		/// <summary>
		/// Return first child UIElement with input name or nullptr if hasn't child with the name.
		/// </summary>
		/// <param name="name"></param>
		/// <returns></returns>
		UIElement*			GetUIElementByName(const string& name) const;

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
			const string*		Name		=nullptr,
			Vector2f			UISize		= DEFAULT_SCALE,
			byte				RendLayer	= DEFAULT_RENDLAYER_UI);

		UIElement(
			Transformable&		Owner,
			const string*		Name		= nullptr,
			Vector2f			UISize		= DEFAULT_SCALE,
			byte				RendLayer	= DEFAULT_RENDLAYER_UI);

		virtual	void SetUISize_Inherit(Vector2f oldSize);
		virtual void SetChildren_UISize(Vector2f oldSize);

		Vector2f		Anchor = Vector2f(0, 0);
		Vector2f		UISize;

		void SetPosition_Inherit() override;
		void SetScale_Inherit() override;
		void SetRotation_Inherit() override;

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
		Vector2f	GetLocalPositionFromParent() const;
		Vector2f	GetLocalScaleFromParent() const;
		Vector2f	TransformLocalPosToGlobal(Vector2f localPos) const;

		string		Name = "";

		Vector2f	LocalPosition = DEFAULT_POSITION;
		Vector2f	LocalScale = DEFAULT_SCALE;

		bool ResizeUIByInherits = false;
	};
}