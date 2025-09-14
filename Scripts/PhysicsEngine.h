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

		enum class PointClassify {
			Left,
			Right,
			Beyond,
			Behind,
			Start,
			End,
			Between
		};

		PhysicsEngine();

		vector<IPhysicalObject*> OverlapAABB_All(Vector2f min, Vector2f max, PhysicsLayer layer=PhysicsLayer::All);
		vector<IPhysicalObject*> OverlapCircle_All(Vector2f center, float radius, PhysicsLayer layer = PhysicsLayer::All);
		vector<IPhysicalObject*> RayCast_All(Vector2f origin, Vector2f direction, float distance, PhysicsLayer layer = PhysicsLayer::All);
		vector<IPhysicalObject*> RayCast_All(const Segment& segm, PhysicsLayer layer = PhysicsLayer::All);

		IPhysicalObject* PointCast(Vector2f globalPos, PhysicsLayer layer = PhysicsLayer::All);

		bool RayHit(Segment segm, PhysicsLayer layer = PhysicsLayer::All);

		static bool Intersect(const Ray& ray, const Segment& seg, Vector2f* interPnt);
		static bool Intersect(const Segment& first, const Segment& second, Vector2f* interPnt);
		static float DistanceToPoint(const Segment& segm,Vector2f pnt);
		static PointClassify Classify(const Segment& segm, Vector2f pnt);

		static inline const EmptyShape& EmptyCollInstance = *new EmptyShape();

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
			size_t objLayer;
			
			for (auto obj : Callbacks) {

				if (obj == nullptr)
					continue;

				objLayer = (size_t)obj->GetLayer();
				layerCast = objLayer & (size_t)layer;
				if (layerCast != 0 && obj->GetCollider().Intersect(shape))
					objs.push_back(obj);
			}
			return objs;
		}
	};
}


