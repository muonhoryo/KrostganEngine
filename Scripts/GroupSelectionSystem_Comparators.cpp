
#include <GroupSelectionSystem.h>
#include <CatalogObject.h>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

bool GroupSelectionSystem::AddSelComparator::Compare
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
//
//
//bool GroupSelectionSystem::EqSelComparator::Equal
//	(watch_ptr_handler_wr<ISelectableEntity>* const& first,watch_ptr_handler_wr<ISelectableEntity>* const& second) const {
//
//	return first->GetPtr_t() == second->GetPtr_t();
//}