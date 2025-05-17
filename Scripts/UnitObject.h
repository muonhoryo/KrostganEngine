#pragma once

#include <SFML/System.hpp>
#include <GameObject.h>
#include <CoreEntitiesControl.h>
#include <Physics.h>
#include <Entity.h>
#include <EntityOrders.h>
#include <vector>
#include <EntityOrderType.h>
#include <EntityBaseAAModule.h>
#include <BaseAutoAggrModule.h>
#include <EntityHPModule.h>

#include <CoreUIUX.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

namespace KrostganEngine {
	namespace GameObjects {
		struct UnitObjectCtorParams : public EntityCtorParams {
			void Init_AAModule(Entity& owner) override {
				AAModule = new EntityBaseAAModule(*BattleStats, owner);
			}
			void Init_AutoAggrModule(Entity& owner,ExecutorActionsMediator& mediator) override {
				AutoAggrModule= new BaseAutoAggrModule(owner, mediator);
			}
			void Init_HPModule() override {
				HPModule = new EntityHPModule(*BattleStats);
			}
		};

		class UnitObject :public Entity {
		public: 
			UnitObject(UnitObjectCtorParams& params);
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
		};
	}
}