#pragma once

#include <ITransformableObj.h>
#include <ICallbackRec.h>
#include <IPhysicalObject.h>

using namespace KrostganEngine::Physics;

namespace KrostganEngine::Core {
	class IWarFogObserver;

	class WarFogObserver_ObsrArea final : public IPhysicalObject{
	
	public:

		//
		// 
		// IPhysicalObject
		//
		//

		PhysicsLayer GetLayer() const override;
		const ColliderShape& GetCollider() const override;

		vector<IPhysicalObject*> OverlapAll() const override;

		//
		//
		// ITransformableObj
		//
		//

		Vector2f			GetGlobalPosition() const override;

		Vector2f			GetGlobalScale() const override;
		Vector2f			GetOrigin() const override;
		const Transform&	GetTransform() const override;
		const Transform&	GetInverseTransform() const override;
		float				GetGlobalRotation() const override;

		Vector2f				GetLocalPosition() const override;
		Vector2f				GetLocalScale() const override;
		float					GetLocalRotation() const override;

		void SetGlobalPosition(Vector2f position) override;
		void SetLocalPosition(Vector2f position) override;

		void SetGlobalScale(Vector2f scale) override;
		void SetLocalScale(Vector2f scale) override;
		void SetOrigin(Vector2f origin) override;
		void SetGlobalRotation(float rotation) override;
		void SetLocalRotation(float rotation) override;

	private:
		WarFogObserver_ObsrArea(IWarFogObserver& owner);
		virtual ~WarFogObserver_ObsrArea(){}

		void UpdateCollider() const;

		mutable CircleCollShape Collider;

		IWarFogObserver& Owner;

		friend class IWarFogObserver;
	};

	class IWarFogObserver : public virtual ITransformableObj, public virtual ICallbackRec {

	public:
		virtual ~IWarFogObserver();

		virtual float GetObservingRange() const = 0;

		bool GetObservingActivity() const;
		
	protected:
		IWarFogObserver(bool isObservingActive=true);

		void SetObservingActive(bool isActive);

	private:
		void SetActive();
		void SetInactive();

		bool IsObservingActive;
		WarFogObserver_ObsrArea* ObservingArea = nullptr;
	};
}