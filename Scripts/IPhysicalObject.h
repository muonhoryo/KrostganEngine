#pragma once

#include <PhysicsLayer.h>
#include <ColliderShapes.h>
#include <ITransfObj.h>
#include <vector>
#include <watch_ptr.h>

using namespace std;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine;

namespace KrostganEngine::Physics {
	class IPhysicalObject: public virtual ITransfObj
	{
	public:

		virtual PhysicsLayer GetLayer() const = 0;
		virtual const ColliderShape& GetCollider() const = 0;

		virtual vector<IPhysicalObject*> OverlapAll() const = 0;

		virtual ~IPhysicalObject();

	protected:
		IPhysicalObject();
	};
}


