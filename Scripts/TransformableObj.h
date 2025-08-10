#pragma once

#include <ITransfObj.h>
#include <SFML/Graphics.hpp>

#define DEFAULT_SCALE		Vector2f(1,1)
#define DEFAULT_POSITION	Vector2f(0,0)
#define DEFAULT_ORIGIN		Vector2f(0,0)

using namespace sf;

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

		void				SetParent				(TransformableObj* parent);
		TransformableObj&	GetParent				();
		virtual void		SetDesWithParent		(bool desWithPar);
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

	private:
		//Vector2f	GlobalScale		= DEFAULT_SCALE;
		Vector2f	LocalPosition	= DEFAULT_POSITION;
		Vector2f	LocalScale		= DEFAULT_SCALE;
		Vector2f	PrevMovStep		= DEFAULT_POSITION;

		Transformable&		Owner;
		TransformableObj*	Parent		= nullptr;
		bool				DesWithPar	= true;

		vector<TransformableObj*> ChildObjs;

		/// <summary>
		/// Calculate local position from parent's transform and owner's transform
		/// </summary>
		/// <returns></returns>
		Vector2f GetLocalPosition_Inter	();
		/// <summary>
		/// 
		/// </summary>
		/// <param name="position"> - global position of object</param>
		/// <param name="isFree"> - is exist parent of this object</param>
		void SetGlobalPosition_Inter	(Vector2f position,bool isFree);

		void SetPosition_Inherit	();
		void SetScale_Inherit		(Vector2f parentGlScale);

		void AddChild		(TransformableObj& child);
		void RemoveChild	(TransformableObj& child);

		friend class TransformableObj;
	};
}