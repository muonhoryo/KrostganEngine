#pragma once

#include <GameObject.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ICallbackRec_Upd.h>
#include <EntityHPModule.h>
#include <vector>
#include <ISelectableEntity.h>
#include <_Events.h>
#include <_RelationsSystem.h>
#include <OrdersExecutor.h>
#include <CallbackDelegates.h>
#include <_ExtGlResources.h>
#include <WarFogObserver.h>
#include <WarFogObserversManager.h>
#include <GameEffectsSystem.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	class Entity;

	struct EntityCtorParams : public GameObjectCtorParams {

		FractionWrapper			EntityFraction = FractionWrapper();

		EntityBattleStats*		BattleStats				=	nullptr;
		const ExtGlRes_Sprite*	SelectionSpriteSource	=	nullptr;
		IndicatorFill*			HPBarSprite				=	nullptr;
		SpriteRenderer*			HitEffectSprite			=	nullptr;
		vector<pair<size_t, std::byte>>	Abilities;
		
		AutoAttackModule*		GetAAModule()			const { return AAModule; }
		AutoAggressionModule*	GetAutoAggrModule()		const { return AutoAggrModule; }
		EntityHPModule*			GetHPModule()			const { return HPModule; }
		IDeathModule*			GetDeathModule()		const { return DeathModule; }
		HPRegenModule*			GetHPRegenModule()		const { return RegenModule; }

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

		Entity* Owner=nullptr;

		friend class Entity;
	};

	class Entity : 
		public GameObject,
		public ISelectableEntity,
		public IAttackableObj,
		public OrdersExecutor, 
		public WarFogObserver, 
		public IGameEffTarget{
	
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

		FractionWrapper GetFraction() const override;

		void SetFraction(FractionWrapper fraction) override;

	//
	// IWarFogObserver
	//

		float GetObservingRange() const override;

	protected:
		Entity(EntityCtorParams& params);

	private:
		void InitializeAbilities(const vector<pair<size_t, std::byte>>& abilities);
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
				UpdateDelayTimer.restart();
			}
			virtual ~OnStealthGraphHider()
			{}

			void Update(CallbackRecArgs_Upd args) override;

		private:
			bool IsOwnerMustHide() {

				Vector2f pos = Owner.GetGlobalPosition();
				FractionWrapper frac = Owner.GetFraction();
				float stealth = Owner.GetBattleStats().GetStealth();

				return !WarFogObserversManager::GetInstance()->Intersect
						(pos, 
						*FractionsSystem::GetFraction(FractionsSystem::PLAYER_FRACTION),
						stealth);
			}

			Entity& Owner;
			bool IsActiveOwner;
			Clock UpdateDelayTimer;
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
		FractionWrapper			EntityFraction = FractionWrapper();

		friend class AutoAggressionModule;

		static const inline string MASK_SHADER_PATH = "Scripts/Shaders/MaskableImage.frag";
	};

	class EntityDeathModule : public IDeathModule {
	public:
		EntityDeathModule(Entity& Owner);

		void Death() override;

	protected:
		Entity& ParOwner;
	};
}