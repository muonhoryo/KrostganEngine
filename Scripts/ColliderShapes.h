#pragma once

#include <SFML/System.hpp>
#include <PhysicsStructs.h>

using namespace std;
using namespace sf;

namespace KrostganEngine::Physics {
	struct AABBCollShape;
	struct CircleCollShape;
	struct EmptyShape;

	struct ColliderShape {
	public:
		virtual ColliderShape& Clone() const = 0;

		virtual bool Intersect(const CircleCollShape& objShape) const = 0;
		virtual bool Intersect(const AABBCollShape& objShape)const = 0;
		virtual bool Intersect(const ColliderShape* coll[], size_t count)const = 0;

		virtual Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir,bool isSlideColl=true) const = 0;
		virtual Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const = 0;

		virtual bool IsPointInCollider(Vector2f point)const = 0;
		virtual Vector2f GetClosestPoint(Vector2f point)const = 0;
		virtual bool IntersectRay(const Ray& ray, Vector2f* interPnt,bool selFarthest=false) const = 0;
		virtual bool IntersectSegment(const Segment& segm) const = 0;

		virtual CircleCollShape GetBoundedCircle()const = 0;

		virtual void SetCenter(Vector2f center) = 0;
		virtual void MoveCollider(Vector2f vec) = 0;
		virtual void Resize(float resizeValue) = 0;

		Vector2f GetCollisionResolvPoint_d(const ColliderShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const;

		static bool Intersect_CircleVsCircle(const CircleCollShape& coll1, const CircleCollShape& coll2);
		static bool Intersect_CircleVsAABB(const CircleCollShape& coll1, const AABBCollShape& coll2);
		static bool Intersect_AABBvsAABB(const AABBCollShape& coll1,const AABBCollShape& coll2);

	protected:
		ColliderShape(){}
	};

	struct AABBCollShape: public ColliderShape
	{
		AABBCollShape(Vector2f Min,Vector2f Max);

		ColliderShape& Clone() const override;

		static AABBCollShape& InstanceBy_CenterAndSize(Vector2f center, float width, float height);

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
		bool IntersectSegment(const Segment& segm) const override;

		CircleCollShape GetBoundedCircle()const override;

		void SetCenter(Vector2f center) override;
		void MoveCollider(Vector2f vec) override;
		void Resize(float resizeValue) override;

		Vector2f GetCenter() const;
		Vector2f GetCornerByMask(size_t mask) const;
		Vector2f GetSize() const;
	};

	struct CircleCollShape: public ColliderShape {
		CircleCollShape(Vector2f Center, float Radius);
		~CircleCollShape(){}

		ColliderShape& Clone() const override;
		
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
		bool IntersectSegment(const Segment& segm) const override;

		CircleCollShape GetBoundedCircle()const override;

		void SetCenter(Vector2f center) override;
		void MoveCollider(Vector2f vec) override;
		void Resize(float resizeValue) override;
	};

	struct EmptyShape :ColliderShape {

		ColliderShape& Clone() const override {
			return *new EmptyShape();
		}

		bool Intersect(const CircleCollShape& collision) const  override {
			return false;
		}
		bool Intersect(const AABBCollShape& collision) const  override {
			return false;
		}
		bool Intersect(const ColliderShape* coll[], size_t count)const override {
			return false;
		}

		Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override {
			return subjShape.Center;
		}
		Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override {
			return subjShape.GetCenter();
		}

		bool IsPointInCollider(Vector2f point) const override {
			return false;
		}
		Vector2f GetClosestPoint(Vector2f point)const override {
			return point;
		}
		bool IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest = false) const override {
			return false;
		}
		bool IntersectSegment(const Segment& segm) const override {
			return false;
		}

		CircleCollShape GetBoundedCircle()const override {
			return CircleCollShape(Vector2f(0,0), 0);
		}

		void SetCenter(Vector2f center) override{}
		void MoveCollider(Vector2f vec) override{}
		void Resize(float resizeValue) override{}

		EmptyShape() : ColliderShape() {

		}
		~EmptyShape() {}
	};
}


