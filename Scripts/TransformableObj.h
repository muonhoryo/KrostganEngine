#pragma once

#include <ITransfObj.h>
#include <SFML/Graphics.hpp>

using namespace sf;

#define DEFAULT_SCALE		Vector2f(1,1)
#define DEFAULT_POSITION	Vector2f(0,0)
#define DEFAULT_ORIGIN		Vector2f(0,0)


namespace KrostganEngine::GameObjects {
	class TransformableObj : public virtual ITransfObj {
	public:
		virtual ~TransformableObj();

		Vector2f			GetGlobalPosition() const override;
		Vector2f			GetLocalPosition() const override;
		Vector2f			GetGlobalScale() const override;
		Vector2f			GetLocalScale() const override;
		Vector2f			GetOrigin() const override;
		Vector2f			GetPrevMovStep() const override;
		const Transform&	GetTransform() const override;
		const Transform&	GetInverseTransform() const override;

		void SetGlobalPosition	(Vector2f position) override;
		void SetLocalPosition	(Vector2f position) override;
		void SetGlobalScale		(Vector2f scale) override;
		void SetLocalScale		(Vector2f scale) override;
		void SetOrigin			(Vector2f origin) override;

		void Move_Global	(Vector2f moveValue) override;
		void Move_Local		(Vector2f moveValue) override;

		void						SetParent	(TransformableObj* parent);
		TransformableObj*			GetParent	();
		TransformableObj const*		GetParent_c	() const;
		/// <summary>
		/// Set is object should be deleted with its parent or not
		/// </summary>
		/// <param name="desWithPar"></param>
		virtual void		SetDesWithParent		(bool desWithPar);
		/// <summary>
		/// Return is object should be deleted with its parent or not
		/// </summary>
		/// <returns></returns>
		bool				GetDesWithParentState	() const;

	protected:
		TransformableObj
			(Transformable&		Owner, 
			TransformableObj&	Parent, 
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			LocalScale		= DEFAULT_SCALE,
			Vector2f			Origin			= DEFAULT_ORIGIN);
		TransformableObj
			(Transformable&		Owner,
			TransformableObj&	Parent,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				LocalScale		= 1,
			Vector2f			Origin			= DEFAULT_ORIGIN);
		TransformableObj
			(Transformable&		Owner, 
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			GlobalScale		= DEFAULT_SCALE,
			Vector2f			Origin			= DEFAULT_ORIGIN);
		TransformableObj
			(Transformable&		Owner,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				GlobalScale		= 1,
			Vector2f			Origin			= DEFAULT_ORIGIN);

		vector<TransformableObj*>::const_iterator GetChildrenStart() const;
		vector<TransformableObj*>::const_iterator GetChildrenEnd() const;

		virtual Vector2f	GetLocalPositionFromParent	();
		virtual Vector2f	GetLocalScaleFromParent		();
		virtual Vector2f	TransformLocalPosToGlobal	(Vector2f localPos);

		/// <summary>
		/// Scale object itself by scale-param
		/// </summary>
		/// <param name="scale"></param>
		virtual void		ScaleObject					(Vector2f scale);

		virtual void		SetChildrenPosition			();
		virtual void		SetChildrenScale			();

		virtual void SetPosition_Inherit();
		virtual void SetScale_Inherit();

	private:
		//Vector2f	GlobalScale		= DEFAULT_SCALE;
		Vector2f	LocalPosition	= DEFAULT_POSITION;
		Vector2f	LocalScale		= DEFAULT_SCALE;
		Vector2f	PrevMovStep		= DEFAULT_POSITION;

		Transformable&		Owner;
		TransformableObj*	Parent		= nullptr;
		bool				DesWithPar	= true;

		vector<TransformableObj*> ChildObjs;

		void AddChild		(TransformableObj& child);
		void RemoveChild	(TransformableObj& child);

		friend class TransformableObj;
	};
}