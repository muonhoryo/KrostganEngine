#pragma once

#include <GameObject.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ICallbackRec_Upd.h>
#include <EntityHPModule.h>
#include <vector>
#include <ISelectableEntity.h>
#include <Events.h>
#include <RelationsSystem.h>
#include <OrdersExecutor.h>
#include <CallbackDelegates.h>
#include <ExtGlResources.h>
#include <WarFogObserver.h>
#include <WarFogObserversManager.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	class Entity;

	struct EntityCtorParams : protected GameObjectCtorParams {

		using GameObjectCtorParams::BodySpriteSource;
		using GameObjectCtorParams::GlobalPosition;
		using GameObjectCtorParams::GlobalScale;
		//SprColor;
		using GameObjectCtorParams::CatalogID;
		using GameObjectCtorParams::SubcatalogID;

		EntityBattleStats*		BattleStats				=	nullptr;
		const ExtGlRes_Sprite*	SelectionSpriteSource			=	nullptr;
		IndicatorFill*			HPBarSprite				=	nullptr;
		SpriteRenderer*			HitEffectSprite			=	nullptr;
		
		AutoAttackModule*		GetAAModule()			const { return AAModule; }
		AutoAggressionModule*	GetAutoAggrModule()		const { return AutoAggrModule; }
		EntityHPModule*			GetHPModule()			const { return HPModule; }
		IDeathModule*			GetDeathModule()		const { return DeathModule; }
		HPRegenModule*			GetHPRegenModule()		const { return RegenModule; }
		Color					GetBodySpriteColor()	const { return SprColor; }
		Fraction				GetFraction()			const { return EntityFraction; }

		void	SetFraction(Fraction fraction) {
			EntityFraction = fraction;
			SprColor = FractionsSystem::GetRelationToPlayerColor(fraction);
		}

	protected:
		virtual void Init_AAModule			() = 0;
		virtual void Init_AutoAggrModule	(ExecutorActionsMediator& mediator) = 0;
		virtual void Init_DeathModule		() = 0;
		virtual void Init_HPModule			() = 0;
		virtual void Init_HPRegenModule		() = 0;

		AutoAttackModule*		AAModule		= nullptr;
		AutoAggressionModule*	AutoAggrModule	= nullptr;
		EntityHPModule*			HPModule		= nullptr;
		IDeathModule*			DeathModule		= nullptr;
		HPRegenModule*			RegenModule		= nullptr;
		Fraction				EntityFraction = Fraction::Neutral;

		Entity* Owner=nullptr;

		friend class Entity;
	};

	class Entity :public GameObject,public ISelectableEntity,public IAttackableObj,public OrdersExecutor, public WarFogObserver{
	public:
		virtual ~Entity();

		void SetRenderActivity(bool isActive);

		bool Get_IsRenderActive() const;

	//
	// ISelectableEntity
	//

		void SelectionOn() override;
		void SelectionOff() override;
		bool IsSelected() override;

	//
	// WorldTransfObj (GameObject)
	//

		void SetGlobalPosition	(Vector2f position) override;
		void SetGlobalScale		(Vector2f scale) override;

	//
	// IColoredObject (GameObject)
	//

		void SetColor(Color color) override;

	//
	// DynamicPhysObject (GameObject)
	//

		void						Update			(CallbackRecArgs_LUpd args) override;
		vector<IPhysicalObject*>	OverlapAll		() const override final;
		const ColliderShape&		GetCollider		() const override final;

		virtual vector<IPhysicalObject*>	OverlapAll_Action() const = 0;
		virtual const ColliderShape&		GetCollider_Action() const = 0;

	//
	// IAttackableObj
	//

		IHitPointModule& GetHPModule() const override;
		bool IsTargetableForAA() const override;

		void SetTargetableForAA(bool isTargetable) override;

	//
	// IFractionMember
	//

		Fraction GetFraction() const override;

		void SetFraction(Fraction fraction) override;

	//
	// IWarFogObserver
	//

		float GetObservingRange() const override;

	protected:
		Entity(EntityCtorParams& params);

	//
	// Stealth-mechanic
	//

	private:
		class OnStealthGraphHider final : public ICallbackRec_Upd {

		public:
			OnStealthGraphHider(Entity& Owner)
				:Owner(Owner) {

				IsActiveOwner = !IsOwnerMustHide();
				Owner.SetRenderActivity(IsActiveOwner);
			}
			virtual ~OnStealthGraphHider()
			{}

			void Update(CallbackRecArgs_Upd args) override {

				if (IsActiveOwner == IsOwnerMustHide()) {

					IsActiveOwner = !IsActiveOwner;
					Owner.SetRenderActivity(IsActiveOwner);
				}
			}

		private:
			bool IsOwnerMustHide() {

				Vector2f pos = Owner.GetGlobalPosition();
				Fraction frac = Owner.GetFraction();
				float stealth = Owner.GetBattleStats().GetStealth();

				return !WarFogObserversManager::GetInstance()->Intersect(pos, Fraction::Player, stealth);
			}

			Entity& Owner;
			bool IsActiveOwner;
		};
		class StealthStatChangedSubs final : public IEventSubscriber<int> {

		public:
			StealthStatChangedSubs(Entity& Owner);
			virtual ~StealthStatChangedSubs(){}

			void Execute(int& args) override;

		private:
			Entity& Owner;

			void ExecuteAction(int args);

			/// <summary>
			/// Initialize stealth-subsystems of entity after the entity has created
			/// </summary>
			struct DelayedInit final : public ICallbackRec_Upd {
			
				DelayedInit(StealthStatChangedSubs& Owner)
					:Owner(Owner)
				{}
				virtual ~DelayedInit(){}

				void Update(CallbackRecArgs_Upd args) override {

					Owner.ExecuteAction((int)EntityBattleStatType::Stealth);
					delete this;
				}

				StealthStatChangedSubs& Owner;
			};
		};

		OnStealthGraphHider* StlHider = nullptr;
		StealthStatChangedSubs StlHider_Subs;

	private:
		
		void Internal_SetRenderActivity(IHierarchyTrObj& target, ICallbackRec_GraphRen* buffer, const bool activity);

		bool					IsEntitySelected		= false;
		bool					IsRenderActive			= true;
		const ExtGlRes_Sprite*	SelectionSpriteSource	= nullptr;
		SpriteRenderer*			SelectionSprite			= nullptr;
		IHitPointModule*		HPModule;
		IndicatorFill*			HPBar;
		SpriteRenderer*			HitEffectSprite;
		Fraction				EntityFraction;

		friend class AutoAggressionModule;

		static const inline string MASK_SHADER_PATH = "Scripts/Shaders/MaskableImage.frag";
	};

	class EntityDeathModule : public IDeathModule {
	public:
		EntityDeathModule(Entity& Owner);

		void Death() override;

	protected:
		Entity& ParOwner;

		class DelayedDeath final: public CallbackDelegate_Upd {
		public:
			DelayedDeath(Entity& Owner):CallbackDelegate_Upd(),
				Owner(Owner){}

			void Execute(CallbackRecArgs_Upd args) override {
				delete& Owner;
			}
		private:
			Entity& Owner;
		};
	};
}