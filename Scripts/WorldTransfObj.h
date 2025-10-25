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

		/// <summary>
		/// Return global scale as float value
		/// </summary>
		/// <returns></returns>
		float GetGlobalScale_Sng() const;
		/// <summary>
		/// Return local scale as float value
		/// </summary>
		/// <returns></returns>
		float GetLocalScale_Sng() const;

		//
		//
		//TransformableObj
		//
		//

		Vector2f			GetLocalPosition() const override;
		Vector2f			GetLocalScale() const override;
		float				GetLocalRotation() const override;

		void SetGlobalPosition	(Vector2f position) override;
		void SetLocalPosition	(Vector2f position) override;

		/// <summary>
		/// Set uniform-only scale to object. Input y-value will be overrided by x-value
		/// </summary>
		/// <param name="scale"></param>
		void SetGlobalScale		(Vector2f scale) override;
		/// <summary>
		/// Set uniform-only scale to object. Input y-value will be overrided by x-value
		/// </summary>
		/// <param name="scale"></param>
		void SetLocalScale		(Vector2f scale) override;

		void SetGlobalRotation(float rotation) override;
		void SetLocalRotation(float rotation) override;

		void SetOrigin			(Vector2f origin) override;

		//
		//
		//IHierarchyTrObj
		//
		//

		void	SetParent			(IHierarchyTrObj* parent) override;

		//
		//
		// IStepTracingObj
		//
		//

		Vector2f GetPrevMovStep() const override;

	protected:
		WorldTransfObj
		(Transformable& Owner,
			WorldTransfObj& Parent,
			Vector2f			GlobalPosition = DEFAULT_POSITION,
			float				LocalScale = DEFAULT_SCALE_SNG,
			float				LocalRotation = 0,
			Vector2f			Origin = DEFAULT_ORIGIN);
		WorldTransfObj
		(Transformable& Owner,
			Vector2f			GlobalPosition = DEFAULT_POSITION,
			float				GlobalScale = DEFAULT_SCALE_SNG,
			float				GlobalRotation = 0,
			Vector2f			Origin = DEFAULT_ORIGIN);

		void SetPosition_Inherit() override;
		void SetScale_Inherit() override;
		void SetRotation_Inherit() override;

	private:
		Vector2f	LocalPosition	= DEFAULT_POSITION;
		float		LocalScale		= DEFAULT_SCALE_SNG;
		Vector2f	PrevMovStep		= DEFAULT_POSITION;
		float		LocalRotation = 0;


		//
		//
		//Internal func
		//
		//

		/// <summary>
		/// Calculate local position of element from parent's transform
		/// </summary>
		/// <returns></returns>
		Vector2f	GetLocalPositionFromParent() const;
		Vector2f	TransformLocalPosToGlobal(Vector2f localPos) const;
	};
}