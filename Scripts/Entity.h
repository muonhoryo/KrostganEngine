#pragma once

#include <Gameobject.h>
#include <CoreEntitiesControl.h>
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

using namespace sf;
using namespace std;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::UI;

namespace KrostganEngine::GameObjects {
	class Entity :public GameObject,public ISelectableEntity, public ICallbackRec_Upd {
	public:
		~Entity();

		void SelectionOn() override;
		void SelectionOff() override;
		bool IsSelected() override;

		void SetPosition(Vector2f position) override;
		void SetScale(float scale) override;

	protected:
		Entity(EntityBattleStats& BattlsStats,const Texture& RenTexture,
			Vector2f RenOffset, Vector2f Position, float Size);

		virtual const Texture& GetSelectionTexture()=0;
		virtual float GetSelectSpriteMaxSize() = 0;
		virtual Vector2f GetSelectSpriteRenOffset() { return Vector2f(0, 0); };

	private:
		bool IsEntitySelected;
		SingleSprite* SelectionSprite;
		//
		// 
		// BattleStats
		// 
		// 
	public:
		EntityBattleStats& BattleStats;
		//
		//
		//Orders system
		//
		//
	public:
		bool TryAddOrder(IEntityOrder* order,bool clearOrdQueue=false);
		void ResetOrdersQueue();

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