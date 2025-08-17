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
#include <HPRegenModules.h>

#include <CoreVisual_UI.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Physics;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

namespace KrostganEngine {
	namespace GameObjects {
		class UnitObject;

		class UnitDeathModule : public EntityDeathModule {
		public:
			UnitDeathModule(Entity& Owner) : EntityDeathModule(Owner) {
			}

			void Death() override;
		};

		struct UnitObjectCtorParams : public EntityCtorParams {
			void Init_AAModule(Entity& owner) override {
				AAModule = new EntityBaseAAModule(*BattleStats, owner);
			}
			void Init_AutoAggrModule(Entity& owner,ExecutorActionsMediator& mediator) override {
				AutoAggrModule= new BaseAutoAggrModule(owner, mediator);
			}
			void Init_DeathModule(Entity& owner) override {
				DeathModule = new UnitDeathModule(owner);
			}
			void Init_HPModule() override {
				HPModule = new EntityHPModule(*GetDeathModule(), *BattleStats,*HPBarSprite);
			}
			void Init_HPRegenModule() override {
				RegenModule = new CommonHPRegenModule(*HPModule);
				((EntityHPModule*)HPModule)->SetRegenModule(RegenModule);
			}
		};

		class UnitObject :public Entity {
		public: 
			UnitObject(UnitObjectCtorParams& params);
			virtual ~UnitObject();

			PhysicsLayer GetLayer() const override;

			void SetGlobalScale(Vector2f size) override;
			void SetGlobalPosition(Vector2f pos) override;

			const vector<EntityOrderType>& GetAllowedOrdersCatalog() override;

		protected:
			vector<IPhysicalObject*> OverlapAll_Action() const override ;
			const ColliderShape& GetCollider_Action() const override;
			Vector2f GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const override;

			Vector2f GetClosestPoint(Vector2f dmgDealerPos) const override;

		private:
			PhysicsLayer Layer;
			CircleCollShape& Collider;
			static const vector<EntityOrderType> AllowedOrdersCatalog;
		};

	}
}