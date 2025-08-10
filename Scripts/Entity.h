#pragma once

#include <GameObject.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SquareScaleSprite.h>
#include <ICallbackRec_Upd.h>
#include <EntityBattleStats.h>
#include <vector>
#include <CoreUIUX.h>
#include <IAttackableObj.h>
#include <AutoAttackModule.h>
#include <ISelectableEntity.h>
#include <Events.h>
#include <RelationsSystem.h>
#include <OrdersExecutor.h>
#include <CallbackDelegates.h>
#include <ExtGlResources.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Visual;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	class Entity;

	struct EntityCtorParams {

		EntityBattleStats*		BattleStats		=	nullptr;
		Fraction				EntityFraction	=	Fraction::Neutral;
		const ExtGlRes_Sprite*	RenSprite		=	nullptr;
		const ExtGlRes_Sprite*	SelectionSprite	=	nullptr;
		Vector2f				GlobalPosition;
		float					LocalScale		=	1;
		IndicatorFill*			HPBarSprite		=	nullptr;
		
		AutoAttackModule*		GetAAModule()			const { return AAModule; }
		AutoAggressionModule*	GetAutoAggrModule()		const { return AutoAggrModule; }
		EntityHPModule*			GetHPModule()			const { return HPModule; }
		IDeathModule*			GetDeathModule()		const { return DeathModule; }
		HPRegenModule*			GetHPRegenModule()		const { return RegenModule; }

	protected:
		virtual void Init_AAModule			(Entity& owner) = 0;
		virtual void Init_AutoAggrModule	(Entity& owner, ExecutorActionsMediator& mediator) = 0;
		virtual void Init_DeathModule		(Entity& owner) = 0;
		virtual void Init_HPModule			() = 0;
		virtual void Init_HPRegenModule		() = 0;

		AutoAttackModule*		AAModule		= nullptr;
		AutoAggressionModule*	AutoAggrModule	= nullptr;
		EntityHPModule*			HPModule		= nullptr;
		IDeathModule*			DeathModule		= nullptr;
		HPRegenModule*			RegenModule		= nullptr;

		friend class Entity;
	};

	class Entity :public GameObject,public ISelectableEntity,public IAttackableObj, public IFractionMember,public OrdersExecutor {
	public:
		virtual ~Entity();

		void SelectionOn() override;
		void SelectionOff() override;
		bool IsSelected() override;

		void SetGlobalPosition	(Vector2f position) override;
		void SetGlobalScale		(Vector2f scale) override;

		void SetColor(Color color) override;

		void						Update			(CallbackRecArgs_LUpd args) override;
		vector<IPhysicalObject*>	OverlapAll		() const override final;
		const ColliderShape&		GetCollider		() const override final;

		virtual vector<IPhysicalObject*>	OverlapAll_Action() const = 0;
		virtual const ColliderShape&		GetCollider_Action() const = 0;

		IHitPointModule& GetHPModule() override;

	protected:
		Entity(EntityCtorParams& params);

	private:
		bool					IsEntitySelected		=	false;
		const ExtGlRes_Sprite*	SelectionSpriteSource	=	nullptr;
		SquareScaleSprite*		SelectionSprite			=	nullptr;
		IHitPointModule*		HPModule;
		IndicatorFill*			HPBar;
		
		friend class AutoAggressionModule;
	public:
		Fraction GetFraction() const override;

	private:
		Fraction EntityFraction;

		Color GetSprColorFromFraction(Fraction frac);

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