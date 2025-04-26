#pragma once

#include <PhysicsLayer.h>
#include <ColliderShapes.h>

namespace KrostganEngine::Physics {
	class IPhysicalObject
	{
	public:

		virtual PhysicsLayer GetLayer() = 0;
		virtual bool IsCollide(AABBCollShape coll) = 0;
		virtual bool IsCollide(CircleCollShape coll) = 0;
		virtual bool IsCollide(ColliderShape* coll[],size_t count) = 0;

		~IPhysicalObject();

	protected:
		IPhysicalObject();
	};
}


