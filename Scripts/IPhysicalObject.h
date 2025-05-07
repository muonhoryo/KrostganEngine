#pragma once

#include <PhysicsLayer.h>
#include <ColliderShapes.h>

namespace KrostganEngine::Physics {
	class IPhysicalObject
	{
	public:

		virtual PhysicsLayer GetLayer() const = 0;
		virtual bool IsCollide(AABBCollShape coll) const = 0;
		virtual bool IsCollide(CircleCollShape coll) const = 0;
		virtual bool IsCollide(ColliderShape* coll[],size_t count) const = 0;
		virtual bool IsInCollider(Vector2f point) const = 0;

		~IPhysicalObject();

	protected:
		IPhysicalObject();
	};
}


