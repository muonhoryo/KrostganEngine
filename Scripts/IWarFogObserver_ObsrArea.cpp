
#include <IWarFogObserver.h>
#include <Engine.h>

using namespace sf;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::Physics;

WarFogObserver_ObsrArea::WarFogObserver_ObsrArea(IWarFogObserver& owner) 
	:ITransformableObj(),
	ICallbackRec(), 
	IPhysicalObject(),
	Owner(Owner),
	Collider(DEFAULT_POSITION,0)
{}

PhysicsLayer WarFogObserver_ObsrArea::GetLayer() const {
	return PhysicsLayer::WarFog;
}
const ColliderShape& WarFogObserver_ObsrArea::GetCollider() const {

	UpdateCollider();
	return Collider;
}

vector<IPhysicalObject*> WarFogObserver_ObsrArea::OverlapAll() const {
	UpdateCollider();
	return Engine::GetPhysicsEngine().OverlapCircle_All(Collider.Center, Collider.Radius, PhysicsLayer::WarFog);
}

void WarFogObserver_ObsrArea::UpdateCollider() const {

	if (Owner.GetObservingActivity()) {
		Collider.Center = Owner.GetGlobalPosition();
		Collider.Radius = Owner.GetObservingRange();
	}
	else {
		Collider.Radius = -1;
	}
}

//
//
//ITransformableObj
//
//

Vector2f			WarFogObserver_ObsrArea::GetGlobalPosition() const { return Owner.GetGlobalPosition();  }

Vector2f			WarFogObserver_ObsrArea::GetGlobalScale() const { return Owner.GetGlobalScale(); }
Vector2f			WarFogObserver_ObsrArea::GetOrigin() const { return Owner.GetOrigin(); }
const Transform&	WarFogObserver_ObsrArea::GetTransform() const { return Owner.GetTransform(); }
const Transform&	WarFogObserver_ObsrArea::GetInverseTransform() const {return Owner.GetInverseTransform(); }
float				WarFogObserver_ObsrArea::GetGlobalRotation() const { return Owner.GetGlobalRotation(); }

Vector2f				WarFogObserver_ObsrArea::GetLocalPosition() const { return Owner.GetLocalPosition(); }
Vector2f				WarFogObserver_ObsrArea::GetLocalScale() const { return Owner.GetLocalScale(); }
float					WarFogObserver_ObsrArea::GetLocalRotation() const { return Owner.GetLocalRotation(); }

void WarFogObserver_ObsrArea::SetGlobalPosition(Vector2f position) { }
void WarFogObserver_ObsrArea::SetLocalPosition(Vector2f position) { }

void WarFogObserver_ObsrArea::SetGlobalScale(Vector2f scale) {}
void WarFogObserver_ObsrArea::SetLocalScale(Vector2f scale) {}
void WarFogObserver_ObsrArea::SetOrigin(Vector2f origin) {}
void WarFogObserver_ObsrArea::SetGlobalRotation(float rotation) {}
void WarFogObserver_ObsrArea::SetLocalRotation(float rotation) {}
