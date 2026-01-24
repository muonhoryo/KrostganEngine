#pragma once

#include <GameObject.h>
#include <SFML/System.hpp>
#include <Physics.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Physics;

namespace KrostganEngine::GameObjects {

	class WallObject :public GameObject {

	public:
		WallObject(const GameObjectCtorParams& params);
		virtual ~WallObject();

		PhysicsLayer GetLayer() const override;

		void SetGlobalPosition(Vector2f position) override;
		void SetGlobalScale(Vector2f scale) override;

	protected:
		const ColliderShape& GetCollider() const override;
		vector<IPhysicalObject*> OverlapAll() const override;
		Vector2f GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const override;

	private:
		AABBCollShape COLLIDER;

		void RecreateCollider();
	};
}