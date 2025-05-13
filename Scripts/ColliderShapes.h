#pragma once

#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::Physics {
	struct AABBCollShape;
	struct CircleCollShape;

	struct ColliderShape {
	public:
		virtual bool Intersect(CircleCollShape collision) const = 0;
		virtual bool Intersect(AABBCollShape collision)const = 0;
		virtual bool IsPointInCollider(Vector2f point)const = 0;
		virtual Vector2f GetClosestPoint(Vector2f point)const = 0;

		static bool Intersect_CircleVsCircle(CircleCollShape coll1, CircleCollShape coll2);
		static bool Intersect_CircleVsAABB(CircleCollShape coll1, AABBCollShape coll2);
		static bool Intersect_AABBvsAABB(AABBCollShape coll1, AABBCollShape coll2);

	protected:
		ColliderShape(){}
	};

	struct AABBCollShape:ColliderShape
	{
		AABBCollShape(Vector2f Min,Vector2f Max);

		 Vector2f Min;
		 Vector2f Max;

		bool Intersect(CircleCollShape collision) const override;
		bool Intersect(AABBCollShape collision) const override;
		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
	};

	struct CircleCollShape:ColliderShape {
		CircleCollShape(Vector2f Center, float Radius);
		
		 Vector2f Center;
		 float Radius;

		bool Intersect(CircleCollShape collision) const  override;
		bool Intersect(AABBCollShape collision) const  override;
		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
	};
}


