#pragma once

#include <SFML/System.hpp>
#include <PhysicsStructs.h>

using namespace std;
using namespace sf;

namespace KrostganEngine::Physics {
	struct AABBCollShape;
	struct CircleCollShape;

	struct ColliderShape {
	public:
		virtual bool Intersect(const CircleCollShape& objShape) const = 0;
		virtual bool Intersect(const AABBCollShape& objShape)const = 0;
		virtual bool Intersect(const ColliderShape* coll[], size_t count)const = 0;

		virtual Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir,bool isSlideColl=true) const = 0;
		virtual Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const = 0;

		virtual bool IsPointInCollider(Vector2f point)const = 0;
		virtual Vector2f GetClosestPoint(Vector2f point)const = 0;
		virtual bool IntersectRay(const Ray& ray, Vector2f* interPnt,bool selFarthest=false) const = 0;

		static bool Intersect_CircleVsCircle(const CircleCollShape& coll1, const CircleCollShape& coll2);
		static bool Intersect_CircleVsAABB(const CircleCollShape& coll1, const AABBCollShape& coll2);
		static bool Intersect_AABBvsAABB(const AABBCollShape& coll1,const AABBCollShape& coll2);

	protected:
		ColliderShape(){}
	};

	struct AABBCollShape:ColliderShape
	{
		AABBCollShape(Vector2f Min,Vector2f Max);

		 Vector2f Min;
		 Vector2f Max;

		bool Intersect(const CircleCollShape& collision) const override;
		bool Intersect(const AABBCollShape& collision) const override;
		bool Intersect(const ColliderShape* coll[], size_t count)const override;

		Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape,Vector2f subjMovDir, bool isSlideColl) const override;
		Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;

		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
		bool IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest=false) const override;

		Vector2f GetCenter() const;
		Vector2f GetCornerByMask(size_t mask) const;
		Vector2f GetSize() const;
	};

	struct CircleCollShape:ColliderShape {
		CircleCollShape(Vector2f Center, float Radius);
		
		 Vector2f Center;
		 float Radius;

		bool Intersect(const CircleCollShape& collision) const  override;
		bool Intersect(const AABBCollShape& collision) const  override;
		bool Intersect(const ColliderShape* coll[], size_t count)const override;

		Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl ) const override;
		Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;

		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
		bool IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest=false) const override;
	};
}


