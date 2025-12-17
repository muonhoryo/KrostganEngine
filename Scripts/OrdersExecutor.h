#pragma once

#include <Events.h>
#include <IEntityAction.h>
#include <IEntityOrder.h>
#include <ICallbackRec_Upd.h>
#include <EntityBattleStats.h>
#include <AutoAttackModule.h>
#include <list>
#include <IFractionMember.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {
	class AutoAggressionModule;
	class ExecutorActionsMediator;

	class OrdersExecutor : public virtual ICallbackRec_Upd, public virtual IFractionMember{
	public:
		virtual ~OrdersExecutor();

		ExecutedEvent<const IEntityOrder> GetOrderEvent;
		ExecutedEvent<const IEntityOrder> StartExecOrderEvent;
		ExecutedEvent<const IEntityOrder> ExecuteOrderEvent;
		NoArgsExecutedEvent ResetOrderListEvent;

		bool TryAddOrder(IEntityOrder& order, bool clearOrdQueue = false);
		bool TryInsertOrder(IEntityOrder& order, size_t insertPos, bool clearOrdQueue = false);
		void ResetOrdersQueue();

		bool GetAbilityToDoOrders() const;
		void AllowOrdersExecution();
		void ProhibitOrdersExecution();

		list<IEntityOrder*>::const_iterator GetOrderQueueIter_Begin() const;
		list<IEntityOrder*>::const_iterator GetOrderQueueIter_AfterEnd() const;
		EntityBattleStats& GetBattleStats() const;
		AutoAttackModule& GetAAModule() const;
		AutoAggressionModule& GetAutoAggrModule() const;

		void Update(CallbackRecArgs_Upd args) override;

	protected:
		OrdersExecutor(EntityBattleStats& BattleStats, AutoAttackModule* AAModule, AutoAggressionModule* AutoAggrModule);

		virtual const vector<EntityOrderType>& GetAllowedOrdersCatalog() = 0;

		ExecutorActionsMediator& GetActionsMediator();

		void SetAAModule(AutoAttackModule* aamodule);
		void SetAutoAggrModule(AutoAggressionModule* autoAggmodule);
	private:
		EventHandler<const IEntityOrder> GetOrderEventHandler = EventHandler<const IEntityOrder>(GetOrderEvent);
		EventHandler<const IEntityOrder> StartExecOrderEventHandler = EventHandler<const IEntityOrder>(StartExecOrderEvent);
		EventHandler<const IEntityOrder> ExecuteOrderEventHandler = EventHandler<const IEntityOrder>(ExecuteOrderEvent);
		NoArgsEventHandler ResetOrderListEventHandler = NoArgsEventHandler(ResetOrderListEvent);

		list<IEntityOrder*> OrdersQueue;
		list<IEntityAction*>* ActionsToExecute;
		IEntityOrder* CurrentOrder;
		IEntityAction* CurrentActionToExecute;

		EntityBattleStats& BattleStats;
		AutoAttackModule* AAModule;
		AutoAggressionModule* AutoAggrModule;

		bool AbleToDoOrders = true;

		void HandleOrders(CallbackRecArgs_Upd& args);
		void HandleActionsToDo(CallbackRecArgs_Upd& args);

		void FirstOrderExecution();
		bool IsFirstOrderExecution();
		void UnloadCurrentOrder();
		void UnloadActionsToDo();
		void UpdateActionsToDoFromOrder();
		void ChangeActionsToDo(list<IEntityAction*>* actions);
		void UpdateCurrActionToExec();

		friend class ExecutorActionsMediator;
	};

	/// <summary>
	/// Provides action's queue changing of OrdersExecutor
	/// </summary>
	class ExecutorActionsMediator final{
	public:
		~ExecutorActionsMediator();

		/// <summary>
		/// Add actions in front of action's list in order: last param is first to execute
		/// </summary>
		/// <typeparam name="TCIterator"></typeparam>
		/// <param name="cbegin"></param>
		/// <param name="after_cend"></param>
		template <typename TCIterator>
		void AddActions(TCIterator cbegin, TCIterator after_cend) {
			for (;cbegin != after_cend;++cbegin) {
				Owner.ActionsToExecute->push_front(*cbegin);
			}
			Owner.UpdateCurrActionToExec();
		}

		void AddAction(IEntityAction* action);
		void SetQueue(list<IEntityAction*>& actions);
		void ResetCurrActions();

		size_t GetActionsCount() const;

	private:
		ExecutorActionsMediator(OrdersExecutor& Owner);

		OrdersExecutor& Owner;

		friend ExecutorActionsMediator& OrdersExecutor::GetActionsMediator();
	};

	class AutoAggressionModule :public ICallbackRec_Upd {

	private:
		class OnStartOrderExecAction : public IEventSubscriber<const IEntityOrder> {
		public:
			OnStartOrderExecAction(AutoAggressionModule& Owner);

			void Execute(const IEntityOrder& ord) override;

		private:
			AutoAggressionModule& Owner;
		};

	public:
		virtual ~AutoAggressionModule();
		void TurnOn();
		void TurnOff();
		void TurnTargetFollowingOn();
		void TurnTargetFollowingOff();
		void Restart();

		virtual bool GetActivityState() const;
		bool GetIsFollTarState()const;

		void Update(CallbackRecArgs_Upd args) override;

	protected:
		AutoAggressionModule(ExecutorActionsMediator& ActionMediator,ExecutedEvent<const IEntityOrder>& StartExecOrderEvent);

		virtual void TurnOnAction();
		virtual void TurnOffAction();
		virtual void TurnTarFollOnAction();
		virtual void TurnTarFollOffAction();
		virtual void UpdateAction(CallbackRecArgs_Upd& args) = 0;

		ExecutorActionsMediator& ActionMediator;
		ExecutedEvent<const IEntityOrder>& StartExecOrderEvent;
		OnStartOrderExecAction& StartExecOrderSubscr;
		bool IsActive;
		bool IsFollowTargets;
	};
}