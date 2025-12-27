#pragma once

#include <PhysicsLayer.h>
#include <ColliderShapes.h>
#include <ITransformableObj.h>
#include <vector>
#include <watch_ptr.h>
#include <ICallbackRec.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine;

namespace KrostganEngine::Physics {
	class IPhysicalObject : public virtual ITransformableObj, public virtual ICallbackRec{
	public:

		virtual PhysicsLayer				GetLayer() const = 0;
		virtual const ColliderShape&		GetCollider() const = 0;
		virtual vector<IPhysicalObject*>	OverlapAll() const = 0;
		virtual bool						IsSolidCollision() const = 0;

		virtual void Set_IsSolidCollision(bool isSolidColl) = 0;

		virtual ~IPhysicalObject();

	protected:
		IPhysicalObject();
	};
}


