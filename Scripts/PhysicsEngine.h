#pragma once

#include <IPhysicalObject.h>
#include <EngineWorkCycleModule.h>
#include <vector>
#include <PhysicsLayer.h>
#include <SFML/System.hpp>
#include <PhysicsStructs.h>

using namespace sf;
using namespace KrostganEngine::Core;

namespace KrostganEngine::Physics {
	class PhysicsEngine: public EngineCallbackHandler<IPhysicalObject>
	{
	public:
		PhysicsEngine();

		vector<IPhysicalObject*> OverlapAABB_All(Vector2f min, Vector2f max, PhysicsLayer layer=PhysicsLayer::All);
		vector<IPhysicalObject*> OverlapCircle_All(Vector2f center, float radius, PhysicsLayer layer = PhysicsLayer::All);

		IPhysicalObject* PointCast(Vector2f globalPos, PhysicsLayer layer = PhysicsLayer::All);

		bool Intersect(const Ray& ray, const Segment& seg, Vector2f* interPnt);

	private:
		/// <summary>
		/// Return empty array if didnt overlap any colliders
		/// </summary>
		/// <typeparam name="TCollShape"></typeparam>
		/// <param name="shape"></param>
		/// <param name="layer"></param>
		/// <returns></returns>
		template<typename TCollShape>
		vector<IPhysicalObject*>Overlap_All(const TCollShape& shape, PhysicsLayer layer = PhysicsLayer::All) {
			vector<IPhysicalObject*> objs = vector<IPhysicalObject*>();
			size_t layerCast;
			for (auto obj : Callbacks) {
				layerCast = (size_t)obj->GetLayer() & (size_t)layer;
				if (layerCast != 0 &&  obj->GetCollider().Intersect(shape))
					objs.push_back(obj);
			}
			return objs;
		}
	};
}


