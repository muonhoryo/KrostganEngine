#pragma once

#include <SFML/System.hpp>
#include <GameObject.h>
#include <CoreEntitiesControl.h>
#include <Physics.h>
#include <Entity.h>
#include <EntityOrders.h>
#include <vector>
#include <EntityOrderType.h>

#include <CoreUIUX.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

namespace KrostganEngine {
	namespace GameObjects {
		class UnitObject :public Entity {
		public: 
			UnitObject(EntityBattleStats& BattleStats,Fraction EntityFraction,const Texture& RenTexture, Vector2f RenOffset, Vector2f Position,float Size);
			~UnitObject();

			PhysicsLayer GetLayer() const override;

			void SetScale(float size) override;
			void SetPosition(Vector2f pos) override;

			const vector<EntityOrderType>& GetAllowedOrdersCatalog() override;

		protected:
			const ColliderShape& GetCollider() const override;
			bool IsCollideShape(const ColliderShape& shape) const override;

			Vector2f GetClosestPoint(Vector2f sources) const override;

			const Texture& GetSelectionTexture() override;
			float GetSelectSpriteMaxSize() override;

		private:
			PhysicsLayer Layer;
			CircleCollShape* Collider;
			static const vector<EntityOrderType> AllowedOrdersCatalog;

			CircleVisPrimitive* testCircle;
		};
	}
}