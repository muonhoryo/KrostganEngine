#pragma once

#include <PhysicsLayer.h>
#include <ColliderShapes.h>
#include <TransformableObj.h>
#include <vector>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Physics {
	class IPhysicalObject: public virtual TransformableObj
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


