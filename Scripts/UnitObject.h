#pragma once

#include <SFML/System.hpp>
#include <GameObject.h>
#include <_CoreEntitiesControl.h>
#include <_Physics.h>
#include <Entity.h>
#include <_EntityOrders.h>
#include <vector>
#include <EntityOrderType.h>
#include <BaseAutoAggrModule.h>
#include <EntityHPModule.h>
#include <_HPRegenModules.h>
#include <_BattleAnimationsExt.h>
#include <EntityAutoAttackModule.h>

#include <_CoreVisual_UI.h>

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

		protected:
			void Init_AAModule() override {
				auto& hitAnim = *new LineAAAnimation(*Owner);
				AAModule = new EntityAutoAttackModule(hitAnim, *Owner);
			}
			void Init_AutoAggrModule(ExecutorActionsMediator& mediator) override {
				AutoAggrModule= new BaseAutoAggrModule(*Owner, mediator);
			}
			void Init_DeathModule() override {
				DeathModule = new UnitDeathModule(*Owner);
			}
			void Init_HPModule() override {
				TakeDamageAnim_SprFade& dmgAnim = *new TakeDamageAnim_SprFade(*HitEffectSprite);
				HPModule = new EntityHPModule(*GetDeathModule(), *BattleStats,*HPBarSprite,dmgAnim);
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

			static inline const PhysicsLayer	GHOST_COLLISION_LAYER = (PhysicsLayer)
				((size_t)PhysicsLayer::Environment |
					(size_t)PhysicsLayer::Decorations |
					(size_t)PhysicsLayer::Buildings);

			PhysicsLayer GetLayer() const override;

			void SetGlobalScale(Vector2f scale) override;
			void SetGlobalPosition(Vector2f pos) override;
			void SetLocalScale(Vector2f scale) override;
			void SetLocalPosition(Vector2f pos) override;

			const vector<EntityOrderType>& GetAllowedOrdersCatalog() override;

		protected:
			vector<IPhysicalObject*> OverlapAll_Action() const override;
			const ColliderShape& GetCollider_Action() const override;
			Vector2f GetResolvingPnt(const ColliderShape& objShape, Vector2f movDir, bool isSlideColl) const override;

			Vector2f GetClosestPoint(Vector2f dmgDealerPos) const override;

		private:
			PhysicsLayer Layer;
			CircleCollShape& COLLIDER;
			static const vector<EntityOrderType> AllowedOrdersCatalog;
		};

	}
}