#pragma once

#include <Gameobject.h>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SingleSprite.h>
#include <IEntityOrder.h>
#include <IEntityAction.h>
#include <ICallbackRec_Upd.h>
#include <list>
#include <EntityBattleStats.h>
#include <vector>
#include <EntityOrderType.h>
#include <CoreUIUX.h>
#include <IHitPointModule.h>
#include <IAttackableObj.h>
#include <AutoAttackModule.h>
#include <ISelectableEntity.h>
#include <Events.h>
#include <RelationsSystem.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

namespace KrostganEngine::GameObjects {
	class Entity :public GameObject,public ISelectableEntity, public ICallbackRec_Upd,public IAttackableObj,
		public IFractionMember{
	public:
		ExecutedEvent<const IEntityOrder*> GetOrderEvent;
		ExecutedEvent<const IEntityOrder*> ExecuteOrderEvent;
		NoArgsExecutedEvent ResetOrderListEvent;

		~Entity();

		void SelectionOn() override;
		void SelectionOff() override;
		bool IsSelected() override;

		void SetPosition(Vector2f position) override;
		void SetScale(float scale) override;
		void SetSpriteColor(Color color) override;

		TransformableObj& GetTransform() override;

	protected:
		Entity(EntityBattleStats& BattlsStats,Fraction EntityFraction,const Texture& RenTexture,
			Vector2f RenOffset, Vector2f Position, float Size);

		virtual const Texture& GetSelectionTexture()=0;
		virtual float GetSelectSpriteMaxSize() = 0;
		virtual Vector2f GetSelectSpriteRenOffset() { return Vector2f(0, 0); };

	private:
		EventHandler<const IEntityOrder*> GetOrderEventHandler = EventHandler<const IEntityOrder*>(GetOrderEvent);
		EventHandler<const IEntityOrder*> ExecuteOrderEventHandler = EventHandler<const IEntityOrder*>(ExecuteOrderEvent);
		NoArgsEventHandler ResetOrderListEventHandler = NoArgsEventHandler(ResetOrderListEventHandler);
		bool IsEntitySelected;
		SingleSprite* SelectionSprite;
		//
		// 
		// BattleStats
		// 
		// 
	public:
		const EntityBattleStats& GetBattleStats();
		IHitPointModule& GetHPModule() override;

	private:
		EntityBattleStats& BattleStats;
		IHitPointModule& HPModule;
		//
		// 
		// Attacking
		// 
		// 
	public:
		AutoAttackModule& GetAAModule();

	private:
		AutoAttackModule& AAModule;
		// 
		//
		//Fraction
		//
		//
	public:
		Fraction GetFraction() const override;

	private:
		Fraction EntityFraction;

		Color GetSprColorFromFraction(Fraction frac);

		// 
		//
		//Orders system
		//
		//
	public:
		bool TryAddOrder(IEntityOrder* order,bool clearOrdQueue=false);
		void ResetOrdersQueue();

		list<IEntityOrder*>::const_iterator GetOrderQueueIter_Begin() const;
		list<IEntityOrder*>::const_iterator GetOrderQueueIter_AfterEnd() const;

		void Update(CallbackRecArgs_Upd args) override;

	protected:
		virtual const vector<EntityOrderType>& GetAllowedOrdersCatalog() = 0;

	private:
		list<IEntityOrder*> OrdersQueue;
		list<IEntityAction*>* ActionsToExecute;
		IEntityOrder* CurrentOrder;
		IEntityAction* CurrentActionToExecute;
		LinesVisPrimitive* OrdersTargetsVisualizer;

		void HandleOrders(CallbackRecArgs_Upd& args);
		void HandleActionsToDo(CallbackRecArgs_Upd& args);

		void FirstOrderExecution();
		bool IsFirstOrderExecution();
		void UnloadCurrentOrder();
		void UpdateActionsToDoFromOrder();
	};
}