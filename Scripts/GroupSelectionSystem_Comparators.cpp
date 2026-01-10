
#include <GroupSelectionSystem.h>
#include <CatalogObject.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

bool GroupSelectionSystem::SelectedEntsComparator::Compare
	(watch_ptr_handler_wr<ISelectableEntity>* const& first, watch_ptr_handler_wr<ISelectableEntity>* const& second) const {

	const CatalogObject* parFirst = dynamic_cast<const CatalogObject*>(first->GetPtr_t_c());
	if (parFirst == nullptr)
		return true;

	const CatalogObject* parSecond = dynamic_cast<const CatalogObject*>(second->GetPtr_t_c());
	if (parSecond == nullptr)
		return false;

	size_t id1 = parFirst->GetCatalogID();
	size_t id2 = parSecond->GetCatalogID();
	if (id1 == id2) {
		return parFirst->GetSubcatalogID() < parSecond->GetSubcatalogID();
	}
	else
		return id1 < id2;
}

GroupSelectionSystem::SelectedEntsPredicate::SelectedEntsPredicate(pair<size_t, std::byte> PredicateValue)
	:PredicateValue(PredicateValue){

}
bool GroupSelectionSystem::SelectedEntsPredicate::Condition
	(watch_ptr_handler_wr<ISelectableEntity>* input) const {

	const CatalogObject* parInput = dynamic_cast<const CatalogObject*>(input->GetPtr_t_c());
	if (parInput == nullptr)
		return PredicateValue.first == 0 &&
			PredicateValue.second == (std::byte)0;

	return parInput->GetCatalogID() == PredicateValue.first && 
		parInput->GetSubcatalogID() == PredicateValue.second;
}
//
//
//bool GroupSelectionSystem::EqSelComparator::Equal
//	(watch_ptr_handler_wr<ISelectableEntity>* const& first,watch_ptr_handler_wr<ISelectableEntity>* const& second) const {
//
//	return first->GetPtr_t() == second->GetPtr_t();
//}