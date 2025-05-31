#pragma once

#include <forward_list>
#include <ISelectableEntity.h>
#include <Events.h>
#include <RelationsSystem.h>

using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::EntitiesControl {
	class GroupSelectionSystem {
	public:
		static inline ExecutedEvent<ISelectableEntity*>& AddSelectableEvent=*new ExecutedEvent<ISelectableEntity*>();
		static inline ExecutedEvent<ISelectableEntity*>& RemoveSelectableEvent= *new ExecutedEvent<ISelectableEntity*>();;
		static inline NoArgsExecutedEvent& ClearSelectionEvent=*new NoArgsExecutedEvent();
		
		~GroupSelectionSystem();

		static GroupSelectionSystem& GetInstance();
		static void Add(ISelectableEntity*& entity);
		static void Remove(ISelectableEntity*& entity);
		static void Clear();

		static forward_list<ISelectableEntity*>::iterator GetEntitiesBegIter() {
			return Singleton->SelectedEntities.begin();
		}
		static forward_list<ISelectableEntity*>::const_iterator GetEntitiesEndIter() {
			return Singleton->SelectedEntities.cend();
		}
		static Relation GetToPlayertRelOfSelEntities() {
			return Singleton->SelEntsRelationToPl;
		}

		template <typename TIterator,typename TCIterator>
		static void AddRange(TIterator itStart, TCIterator itEnd) {
			while (itStart != itEnd) {
				Add(*itStart);
				++itStart;
			}
		}
	private:
		EventHandler<ISelectableEntity*> AddSelectableEventHandler = EventHandler<ISelectableEntity*>(AddSelectableEvent);
		EventHandler<ISelectableEntity*> RemoveSelectableEventHandler = EventHandler<ISelectableEntity*>(RemoveSelectableEvent);
		NoArgsEventHandler ClearSelectionEventHandler = NoArgsEventHandler(ClearSelectionEvent);

		GroupSelectionSystem();

		static GroupSelectionSystem* Singleton;

		forward_list<ISelectableEntity*> SelectedEntities;
		Relation SelEntsRelationToPl;
		Fraction SelEntsFraction;
	};
}