#pragma once

#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::Physics {
	struct AABBCollShape;
	struct CircleCollShape;

	struct ColliderShape {
	public:
		virtual bool IsOverlap(CircleCollShape collision) const = 0;
		virtual bool IsOverlap(AABBCollShape collision)const = 0;
		virtual bool IsPointInCollider(Vector2f point)const = 0;
		virtual Vector2f GetClosestPoint(Vector2f point)const = 0;

		static bool IsOverlap_CircleVsCircle(CircleCollShape coll1, CircleCollShape coll2);
		static bool IsOverlap_CircleVsAABB(CircleCollShape coll1, AABBCollShape coll2);
		static bool IsOverlap_AABBvsAABB(AABBCollShape coll1, AABBCollShape coll2);

		static bool IsPointInCollider(const CircleCollShape& coll, Vector2f point);
		static bool IsPointInCollider(const AABBCollShape& coll, Vector2f point);

		static Vector2f GetClosestPoint(const CircleCollShape& coll, Vector2f point);
		static Vector2f GetClosestPoint(const AABBCollShape& coll, Vector2f point);

	protected:
		ColliderShape(){}
	};

	struct AABBCollShape:ColliderShape
	{
		AABBCollShape(Vector2f Min,Vector2f Max);

		 Vector2f Min;
		 Vector2f Max;

		bool IsOverlap(CircleCollShape collision) const override;
		bool IsOverlap(AABBCollShape collision) const override;
		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
	};

	struct CircleCollShape:ColliderShape {
		CircleCollShape(Vector2f Center, float Radius);
		
		 Vector2f Center;
		 float Radius;

		bool IsOverlap(CircleCollShape collision) const  override;
		bool IsOverlap(AABBCollShape collision) const  override;
		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
	};
}


