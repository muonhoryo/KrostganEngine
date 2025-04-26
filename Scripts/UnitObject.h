#pragma once

#include <SFML/System.hpp>
#include <GameObject.h>
#include <EntitiesControl.h>
#include <Physics.h>
#include <Entity.h>

#include <CoreUIUX.h>

using namespace sf;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

namespace KrostganEngine {
	namespace GameObjects {
		class UnitObject :public Entity {
		public: 
			UnitObject(const Texture& RenTexture, Vector2f RenOffset, Vector2f Position,float Size);
			~UnitObject();

			PhysicsLayer GetLayer() override;

			void SetScale(float size) override;
			void SetPosition(Vector2f pos) override;

		protected:
			const ColliderShape& GetCollider() const override;
			bool IsCollideShape(const ColliderShape& shape) const override;
			const Texture& GetSelectionTexture() override;
			float GetSelectSpriteMaxSize() override;

		private:
			PhysicsLayer Layer;
			CircleCollShape* Collider;

			CircleVisPrimitive* testCircle;
		};
	}
}