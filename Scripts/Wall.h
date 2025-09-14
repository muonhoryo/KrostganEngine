#pragma once

#include <GameObject.h>
#include <SFML/System.hpp>
#include <Physics.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Physics;

namespace KrostganEngine::GameObjects {

	class WallObject;

	struct WallCtorParams : protected GameObjectCtorParams {
		
		WallCtorParams():GameObjectCtorParams(){}

		using GameObjectCtorParams::BodySpriteSource;
		using GameObjectCtorParams::GlobalPosition;
		using GameObjectCtorParams::GlobalScale;

		friend class WallObject;
	};

	class WallObject :public GameObject {

	public:
		WallObject(const WallCtorParams& params);
		virtual ~WallObject();

		PhysicsLayer GetLayer() const override;

		void SetGlobalPosition(Vector2f position) override;
		void SetGlobalScale(Vector2f scale) override;

	protected:
		const ColliderShape& GetCollider() const override;
		vector<IPhysicalObject*> OverlapAll() const override;
		Vector2f GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const override;

	private:
		AABBCollShape* Collider;

		void RecreateCollider();
	};
}