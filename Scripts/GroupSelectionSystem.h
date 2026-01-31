#pragma once

#include <forward_list>
#include <ISelectableEntity.h>
#include <RelationsSystem.h>
#include <IAttackableObj.h>
#include <watch_ptr_predicates.h>
#include <Events.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class GroupSelectionSystem final {

	private:
		struct SelectedEntsComparator : public CollectionsExts::CompareFunc<watch_ptr_handler_wr<ISelectableEntity>*> {

			bool Compare
			(watch_ptr_handler_wr<ISelectableEntity>* const& first,
				watch_ptr_handler_wr<ISelectableEntity>* const& second) const override;
		};
		struct SelectedEntsPredicate : public CollectionsExts::Predicate<watch_ptr_handler_wr<ISelectableEntity>*> {

			SelectedEntsPredicate(pair<size_t, std::byte> PredicateValue);

			bool Condition(watch_ptr_handler_wr<ISelectableEntity>* input) const override;

			pair<size_t, std::byte> PredicateValue;
		};

		static inline const SelectedEntsComparator InstanceAddComparator;
		static inline const w_ptr_han_pred_eqByOwners<watch_ptr_handler_wr<ISelectableEntity>> InstanceEqComparator;

		struct DeathEventSubscr : public IEventSubscriber<const GlObjectDeathEventArgs> {
			void Execute(const GlObjectDeathEventArgs& args) override {
				auto deadObj = dynamic_cast<ISelectableEntity*>(&args.Owner);
				if (deadObj != nullptr) {
					auto& ptr = deadObj->GetPtr();
					auto& ptr_wr = *new watch_ptr_handler_wr<ISelectableEntity>(ptr);
					delete &ptr;
					if (CollectionsExts::Contains(Singleton->SelectedEntities, &ptr_wr, InstanceEqComparator)) {
						
						Remove(*deadObj);
					}
					delete& ptr_wr;
				}
			}
		};

	public:
		static inline NoArgsExecutedEvent					ChangeSelectablesEvent	= NoArgsExecutedEvent();
		static inline ExecutedEvent<ISelectableEntity>		AddSelectableEvent		= ExecutedEvent<ISelectableEntity>();
		static inline ExecutedEvent<ISelectableEntity>		RemoveSelectableEvent	= ExecutedEvent<ISelectableEntity>();
		static inline NoArgsExecutedEvent					ClearSelectionEvent		= NoArgsExecutedEvent();

		static inline NoArgsExecutedEvent						ChangeChoosenEntsEvent		= NoArgsExecutedEvent();
		static inline ExecutedEvent<ISelectableEntity>			AddEntToChoosenEvent		= ExecutedEvent<ISelectableEntity>();
		static inline ExecutedEvent<ISelectableEntity>			RemoveEntFromChoosenEvent	= ExecutedEvent<ISelectableEntity>();
		static inline ExecutedEvent<pair<size_t, std::byte>>	ChangeChoosenGroupEvent		= ExecutedEvent<pair<size_t, std::byte>>();

		~GroupSelectionSystem();

		static GroupSelectionSystem& GetInstance();
		static void Add(ISelectableEntity& entity);
		static void Remove(ISelectableEntity& entity);
		static void Clear();

	//Selected entities

		static forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::iterator			GetSelectedEnts_Begin() {
			return Singleton->SelectedEntities.begin();
		}
		static forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::const_iterator	GetSelectedEnts_End() {
			return Singleton->SelectedEntities.cend();
		}
		static Relation				GetToPlayertRelOfSelEntities() {
			return Singleton->SelEntsRelationToPl;
		}
		static ISelectableEntity*	GetFirstSelected() {
			size_t size = GetSelectionCount();
			return size == 0 ? nullptr : Singleton->SelectedEntities.front()->GetPtr_t();
		}
		static size_t				GetSelectionCount() {
			auto& coll = Singleton->SelectedEntities;
			return distance(coll.begin(), coll.end());
		}

	//Choosen entities

		static forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::iterator			GetChoosenEntities_Begin();
		static forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::const_iterator	GetChoosenEntities_End();
		static ISelectableEntity*		GetFirstChoosen() {
			forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::const_iterator itBeg_c = GetChoosenEntities_Begin();
			auto itEnd = GetChoosenEntities_End();
			size_t size = distance(itBeg_c, itEnd);
			return size == 0 ? nullptr : (*itBeg_c)->GetPtr_t();
		}
		static size_t					GetChoosenGroupCount() {
			forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::const_iterator itBeg_c = GetChoosenEntities_Begin();
			return distance(itBeg_c, GetChoosenEntities_End());
		}
		static pair<size_t, std::byte>	GetCurrChooseGroupInfo() {
			return Singleton->ChoosenEntitesCatalInfo;
		}
		/// <summary>
		/// Return catalog info of choosen entities
		/// </summary>
		/// <returns></returns>
		static pair<size_t, std::byte>	ChoiseNextEntsGroup();
		/// <summary>
		/// Return catalog info of choosen entities
		/// </summary>
		/// <returns></returns>
		static pair<size_t, std::byte>	ChoisePrevEntsGroup();

		template <typename TCIterator>
		static void AddRange(TCIterator itStart, TCIterator itEnd) {
			while (itStart != itEnd) {
				Add(**itStart);
				++itStart;
			}
		}

		template <typename TCIterator>
		static void RemoveRange(TCIterator itStart, TCIterator itEnd) {
			while (itStart != itEnd) {
				Remove(**itStart);
				++itStart;
			}
		}

	private:
		NoArgsEventHandler					ChangeSelectablesEventHandler = NoArgsEventHandler(ChangeSelectablesEvent);
		EventHandler<ISelectableEntity>		AddSelectableEventHandler = EventHandler<ISelectableEntity>(AddSelectableEvent);
		EventHandler<ISelectableEntity>		RemoveSelectableEventHandler = EventHandler<ISelectableEntity>(RemoveSelectableEvent);
		NoArgsEventHandler					ClearSelectionEventHandler = NoArgsEventHandler(ClearSelectionEvent);

		static inline NoArgsEventHandler						ChangeChoosenEntsEvHan = NoArgsEventHandler(ChangeChoosenEntsEvent);
		static inline EventHandler<ISelectableEntity>			AddEntToChoosenEvHan = EventHandler<ISelectableEntity>(AddEntToChoosenEvent);
		static inline EventHandler<ISelectableEntity>			RemoveEntFromChoosenEvHan = EventHandler<ISelectableEntity>(RemoveEntFromChoosenEvent);
		static inline EventHandler<pair<size_t, std::byte>>		ChangeChoosenGroupEvHan = EventHandler<pair<size_t, std::byte>>(ChangeChoosenGroupEvent);

		GroupSelectionSystem();

		static inline GroupSelectionSystem* Singleton = nullptr;

		/// <summary>
		/// Insert element by sorting order
		/// </summary>
		/// <param name="entity"></param>
		static void Add_inter(watch_ptr_handler_wr<ISelectableEntity>* entity);
		static void RemoveNullable();
		static SelectedEntsPredicate GetPredForCurrChoosenGroup();

		forward_list<watch_ptr_handler_wr<ISelectableEntity>*>	SelectedEntities;
		Relation												SelEntsRelationToPl		= Relation::Neutral;
		const Fraction*											SelEntsFraction			= nullptr;
		pair<size_t, std::byte>									ChoosenEntitesCatalInfo = ZERO_CHOISE;
		DeathEventSubscr*										DeathEvSubs;

		static inline const pair<size_t, std::byte> ZERO_CHOISE = pair<size_t, std::byte>(0, (std::byte)0);
	};
}