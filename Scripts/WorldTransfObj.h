#pragma once

#include <HierarchyTrObj.h>
#include <SFML/Graphics.hpp>
#include <IStepTracingObj.h>

using namespace sf;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	class WorldTransfObj;

	class WorldTransfObj : public HierarchyTrObj, public virtual IStepTracingObj {
	public:
		virtual ~WorldTransfObj(){}

		//
		//
		//TransformableObj
		//
		//

		Vector2f			GetLocalPosition() const override;
		Vector2f			GetLocalScale() const override;

		void SetGlobalPosition	(Vector2f position) override;
		void SetLocalPosition	(Vector2f position) override;
		void SetGlobalScale		(Vector2f scale) override;
		void SetLocalScale		(Vector2f scale) override;
		void SetOrigin			(Vector2f origin) override;

		//
		//
		//IHierarchyTrObj
		//
		//

		void	SetParent			(IHierarchyTrObj* parent) override;

		void SetPosition_Inherit() override;
		void SetScale_Inherit() override;

		//
		//
		// IStepTracingObj
		//
		//

		Vector2f GetPrevMovStep() const override;

	protected:
		WorldTransfObj
			(Transformable&		Owner, 
			WorldTransfObj&		Parent, 
			Vector2f			LocalPosition = DEFAULT_POSITION,
			Vector2f			LocalScale		= DEFAULT_SCALE,
			Vector2f			Origin			= DEFAULT_ORIGIN);
		WorldTransfObj
			(Transformable&		Owner,
			WorldTransfObj&	Parent,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				LocalScale		= 1,
			Vector2f			Origin			= DEFAULT_ORIGIN);
		WorldTransfObj
			(Transformable&		Owner, 
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			Vector2f			GlobalScale		= DEFAULT_SCALE,
			Vector2f			Origin			= DEFAULT_ORIGIN);
		WorldTransfObj
			(Transformable&		Owner,
			Vector2f			GlobalPosition	= DEFAULT_POSITION,
			float				GlobalScale		= 1,
			Vector2f			Origin			= DEFAULT_ORIGIN);


	private:
		Vector2f	LocalPosition	= DEFAULT_POSITION;
		Vector2f	LocalScale		= DEFAULT_SCALE;
		Vector2f	PrevMovStep		= DEFAULT_POSITION;


		//
		//
		//Internal func
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
		void	ScaleObject			(Vector2f scale);

		//friend class TransformableObj;
	};
}