#pragma once

#include <GameObject.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SingleSprite.h>
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

using namespace sf;
using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Visual;

namespace KrostganEngine::GameObjects {
	class Entity;

	struct EntityCtorParams {
		EntityBattleStats* BattleStats=nullptr;
		Fraction EntityFraction=Fraction::Neutral;
		const Texture* RenTexture=nullptr;
		Vector2f RenOffset;
		Vector2f Position;
		float Size;

		AutoAttackModule* GetAAModule() const { return AAModule; }
		AutoAggressionModule* GetAutoAggrModule() const { return AutoAggrModule; }
		IHitPointModule* GetHPModule() const { return HPModule; }
		IDeathModule* GetDeathModule() const { return DeathModule; }

	protected:
		virtual void Init_AAModule(Entity& owner) = 0;
		virtual void Init_AutoAggrModule(Entity& owner, ExecutorActionsMediator& mediator) = 0;
		virtual void Init_DeathModule(Entity& owner) = 0;
		virtual void Init_HPModule() = 0;

		AutoAttackModule* AAModule=nullptr;
		AutoAggressionModule* AutoAggrModule=nullptr;
		IHitPointModule* HPModule=nullptr;
		IDeathModule* DeathModule = nullptr;

		friend class Entity;
	};

	class Entity :public GameObject,public ISelectableEntity,public IAttackableObj, public IFractionMember,public OrdersExecutor {
	public:
		virtual ~Entity();

		void SelectionOn() override;
		void SelectionOff() override;
		bool IsSelected() override;

		void SetPosition(Vector2f position) override;
		void SetScale(float scale) override;
		void SetSpriteColor(Color color) override;

		void RenderGraphic(RenderWindow& window) override;
		void Update(CallbackRecArgs_LUpd args) override;
		vector<IPhysicalObject*> OverlapAll() const override final;
		const ColliderShape& GetCollider() const override final;

		virtual vector<IPhysicalObject*> OverlapAll_Action() const = 0;
		virtual const ColliderShape& GetCollider_Action() const = 0;

		IHitPointModule& GetHPModule()override;

	protected:
		Entity(EntityCtorParams& params);

		virtual const Texture& GetSelectionTexture()=0;
		virtual float GetSelectSpriteMaxSize() = 0;
		virtual Vector2f GetSelectSpriteRenOffset() { return Vector2f(0, 0); };

	private:
		bool IsEntitySelected;
		SingleSprite* SelectionSprite;
		IHitPointModule* HPModule;
		
		friend class AutoAggressionModule;
	public:
		Fraction GetFraction() const override;

	private:
		Fraction EntityFraction;

		Color GetSprColorFromFraction(Fraction frac);
	};

	class EntityDeathModule : public IDeathModule {
	public:
		EntityDeathModule(Entity& Owner);

		void Death() override;

	protected:
		Entity& ParOwner;
	};
}