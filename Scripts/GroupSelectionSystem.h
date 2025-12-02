#pragma once

#include <forward_list>
#include <ISelectableEntity.h>
#include <Events.h>
#include <RelationsSystem.h>
#include <CollectionsExts.h>
#include <IAttackableObj.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class GroupSelectionSystem final {

	private:
		struct AddSelComparator : public CollectionsExts::CompareFunc<watch_ptr_handler_wr<ISelectableEntity>*> {

			bool Compare
				(watch_ptr_handler_wr<ISelectableEntity>* const& first,
				watch_ptr_handler_wr<ISelectableEntity>* const& second) const override;
		};
		struct EqSelComparator : public CollectionsExts::EqualCompareFunc<watch_ptr_handler_wr<ISelectableEntity>*> {

			bool Equal
				(watch_ptr_handler_wr<ISelectableEntity>* const& first,
				watch_ptr_handler_wr<ISelectableEntity>* const& second) const override;
		};

		static inline const AddSelComparator InstanceAddComparator;
		static inline const EqSelComparator InstanceEqComparator;

		struct DeathEventSubscr : public IEventSubscriber<const GlObjectDeathEventArgs> {
			void Execute(const GlObjectDeathEventArgs& args) override {
				auto deadObj = dynamic_cast<ISelectableEntity*>(&args.Owner);
				if (deadObj != nullptr) {
					auto& ptr = deadObj->GetPtr();
					auto& ptr_wr = *new watch_ptr_handler_wr<ISelectableEntity>(ptr);
					delete &ptr;
					if (CollectionsExts::Contains(Singleton->SelectedEntities, &ptr_wr,InstanceEqComparator)) {
						Remove(*deadObj);
					}
					delete& ptr_wr;
				}
			}
		};

	public:
		static inline NoArgsExecutedEvent					ChangeSelectablesEvent	= NoArgsExecutedEvent();
		static inline ExecutedEvent<ISelectableEntity>		AddSelectableEvent		= ExecutedEvent<ISelectableEntity>();
		static inline ExecutedEvent<ISelectableEntity>		RemoveSelectableEvent	= ExecutedEvent<ISelectableEntity>();;
		static inline NoArgsExecutedEvent					ClearSelectionEvent		= NoArgsExecutedEvent();
		
		~GroupSelectionSystem();

		static GroupSelectionSystem& GetInstance();
		static void Add(ISelectableEntity& entity);
		static void Remove(ISelectableEntity& entity);
		static void Clear();

		static forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::iterator			GetEntitiesBegIter() {
			return Singleton->SelectedEntities.begin();
		}
		static forward_list<watch_ptr_handler_wr<ISelectableEntity>*>::const_iterator	GetEntitiesEndIter() {
			return Singleton->SelectedEntities.cend();
		}
		static Relation				GetToPlayertRelOfSelEntities() {
			return Singleton->SelEntsRelationToPl;
		}
		static ISelectableEntity*	GetFirstSelectable() {
			size_t size = CollectionsExts::Size<forward_list<watch_ptr_handler_wr<ISelectableEntity>*>>
				(Singleton->SelectedEntities);
			return size == 0 ? nullptr : Singleton->SelectedEntities.front()->GetPtr_t();
		}
		static size_t					GetSelectionCount() {
			auto& coll = Singleton->SelectedEntities;
			return distance(coll.begin(), coll.end());
		}

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

		GroupSelectionSystem();

		static GroupSelectionSystem* Singleton;

		/// <summary>
		/// Insert element by sorting order
		/// </summary>
		/// <param name="entity"></param>
		static void Add_inter(watch_ptr_handler_wr<ISelectableEntity>* entity);

		forward_list<watch_ptr_handler_wr<ISelectableEntity>*>	SelectedEntities;
		Relation												SelEntsRelationToPl		= Relation::Neutral;
		Fraction												SelEntsFraction			= Fraction::Neutral;
		DeathEventSubscr*										DeathEvSubs;
	};
}