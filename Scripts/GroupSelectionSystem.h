#pragma once

#include <forward_list>
#include <ISelectableEntity.h>

using namespace std;

namespace KrostganEngine::EntitiesControl {
	class GroupSelectionSystem {
	public:
		~GroupSelectionSystem();

		static GroupSelectionSystem& GetInstance();
		static void Add(ISelectableEntity*& entity);
		static void Remove(ISelectableEntity*& entity);
		static void Clear();
		static forward_list<ISelectableEntity*>::iterator GetEntitiesBegIter();
		static forward_list<ISelectableEntity*>::const_iterator GetEntitiesEndIter();

		template <typename TIterator,typename TCIterator>
		static void AddRange(TIterator itStart, TCIterator itEnd) {
			while (itStart != itEnd) {
				Add(*itStart);
				++itStart;
			}
		}
	private:
		GroupSelectionSystem();

		static GroupSelectionSystem* Singleton;

		forward_list<ISelectableEntity*> SelectedEntities;
	};
}