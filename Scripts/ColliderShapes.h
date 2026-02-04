#pragma once

#include <SFML/System.hpp>
#include <PhysicsStructs.h>
#include <vector>

using namespace std;
using namespace sf;

namespace KrostganEngine::Physics {
	struct CircleCollShape;
	struct AABBCollShape;
	struct PolygonCollShape;
	struct EmptyShape;

	struct ColliderShape {
	public:
		virtual ~ColliderShape(){}

		virtual ColliderShape& Clone() const = 0;

		virtual bool Intersect(const CircleCollShape& objShape) const = 0;
		virtual bool Intersect(const AABBCollShape& objShape)const = 0;
		virtual bool Intersect(const PolygonCollShape& objShape) const = 0;
		virtual bool Intersect(const ColliderShape* coll[], size_t count)const = 0;

		virtual Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir,bool isSlideColl=true) const = 0;
		virtual Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const = 0;
		virtual Vector2f GetCollisionResolvPoint(const PolygonCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const = 0;

		virtual bool IsPointInCollider(Vector2f point)const = 0;
		virtual Vector2f GetClosestPoint(Vector2f point)const = 0;
		virtual bool IntersectRay(const Ray& ray, Vector2f* interPnt,bool selFarthest=false) const = 0;
		virtual bool IntersectSegment(const Segment& segm) const = 0;

		virtual const CircleCollShape& GetOutterBoundCircle()const = 0;

		virtual void SetCenter(Vector2f center) = 0;
		virtual void MoveCollider(Vector2f vec) = 0;
		virtual void Resize(float resizeValue) = 0;

		Vector2f GetCollisionResolvPoint_d(const ColliderShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const;

		static bool Intersect_CircleVsCircle(const CircleCollShape& coll1, const CircleCollShape& coll2);
		static bool Intersect_CircleVsAABB(const CircleCollShape& coll1, const AABBCollShape& coll2);
		static bool Intersect_AABBvsAABB(const AABBCollShape& coll1,const AABBCollShape& coll2);
		static bool Intersect_PolygonVsCircle(const PolygonCollShape& coll1, const CircleCollShape& coll2);
		static bool Intersect_PolygonVsAABB(const PolygonCollShape& col11, const AABBCollShape& coll2);
		static bool Intersect_PolygonVsPolygon(const PolygonCollShape& coll1, const PolygonCollShape& coll2);

	protected:
		ColliderShape(){}
	};

	struct CircleCollShape : public ColliderShape {
		CircleCollShape(Vector2f Center, float Radius);
		virtual ~CircleCollShape() {}

		ColliderShape& Clone() const override;

		Vector2f Center;
		float Radius;

		bool Intersect(const CircleCollShape& collision) const  override;
		bool Intersect(const AABBCollShape& collision) const  override;
		bool Intersect(const PolygonCollShape& objShape) const override;
		bool Intersect(const ColliderShape* coll[], size_t count)const override;

		Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;
		Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;
		Vector2f GetCollisionResolvPoint(const PolygonCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;

		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
		bool IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest = false) const override;
		bool IntersectSegment(const Segment& segm) const override;

		const CircleCollShape& GetOutterBoundCircle()const override;

		void SetCenter(Vector2f center) override;
		void MoveCollider(Vector2f vec) override;
		void Resize(float resizeValue) override;
	};

	struct AABBCollShape: public ColliderShape
	{
		AABBCollShape(Vector2f Min,Vector2f Max);
		virtual ~AABBCollShape(){}

		ColliderShape& Clone() const override;

		static AABBCollShape& InstanceBy_CenterAndSize(Vector2f center, float width, float height);

		 Vector2f Min;
		 Vector2f Max;

		bool Intersect(const CircleCollShape& collision) const override;
		bool Intersect(const AABBCollShape& collision) const override;
		bool Intersect(const PolygonCollShape& objShape) const override;
		bool Intersect(const ColliderShape* coll[], size_t count)const override;

		Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape,Vector2f subjMovDir, bool isSlideColl) const override;
		Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;
		Vector2f GetCollisionResolvPoint(const PolygonCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const override;

		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
		bool IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest=false) const override;
		bool IntersectSegment(const Segment& segm) const override;

		const CircleCollShape& GetOutterBoundCircle()const override;

		void SetCenter(Vector2f center) override;
		void MoveCollider(Vector2f vec) override;
		void Resize(float resizeValue) override;

		Vector2f GetCenter() const;
		Vector2f GetCornerByMask(size_t mask) const;
		Vector2f GetSize() const;

	private:
		mutable CircleCollShape BoundCircle;

		void UpdateBoundCirclePos() const;
	};

	struct PolygonCollShape : public ColliderShape {
		PolygonCollShape(vector<Vector2f>& Points);
		virtual ~PolygonCollShape();

		ColliderShape& Clone() const override;

		bool Intersect(const CircleCollShape& collision) const  override;
		bool Intersect(const AABBCollShape& collision) const  override;
		bool Intersect(const PolygonCollShape& objShape) const override;
		bool Intersect(const ColliderShape* coll[], size_t count)const override;

		Vector2f GetCollisionResolvPoint(const CircleCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;
		Vector2f GetCollisionResolvPoint(const AABBCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;
		Vector2f GetCollisionResolvPoint(const PolygonCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl) const override;

		bool IsPointInCollider(Vector2f point) const override;
		Vector2f GetClosestPoint(Vector2f point)const override;
		bool IntersectRay(const Ray& ray, Vector2f* interPnt, bool selFarthest) const override;
		bool IntersectSegment(const Segment& segm) const override;

		const CircleCollShape& GetOutterBoundCircle()const override;

		void SetCenter(Vector2f center) override;
		void MoveCollider(Vector2f vec) override;
		void Resize(float resizeValue) override;

		const vector<Vector2f>& GetPoints() const;

		//TODO
		//Make a functionality to change points' collection

	private:
		mutable CircleCollShape BoundCircle;

		void InitBoundCircles();

		vector<Vector2f>& Points;
	};

	struct EmptyShape : public ColliderShape {

		EmptyShape() : ColliderShape() {}
		virtual ~EmptyShape() {}

		ColliderShape& Clone() const override {
			return *new EmptyShape();
		}

		CircleCollShape empty = CircleCollShape(Vector2f(0,0),0);

		bool Intersect(const CircleCollShape& collision) const  override {
			return false;
		}
		bool Intersect(const AABBCollShape& collision) const  override {
			return false;
		}
		bool Intersect(const PolygonCollShape& objShape) const override {
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
		Vector2f GetCollisionResolvPoint(const PolygonCollShape& subjShape, Vector2f subjMovDir, bool isSlideColl = true) const override {
			return subjShape.GetOutterBoundCircle().Center;
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

		const CircleCollShape& GetOutterBoundCircle()const override {
			return empty;
		}

		void SetCenter(Vector2f center) override{}
		void MoveCollider(Vector2f vec) override{}
		void Resize(float resizeValue) override{}
	};
}


