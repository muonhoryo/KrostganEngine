
#include <AbilitiesSystem.h>

using namespace KrostganEngine::GameObjects;

AbilityUserObject::AbilityUserObject() {

}
AbilityUserObject::~AbilityUserObject() {

	if (Abilities != nullptr) {

		for (auto ab : *Abilities) {
			ab->OnRemoveFromUser(*this);
			delete ab;
		}
		delete Abilities;
	}
}

size_t AbilityUserObject::AddNewAbilityToArr(Ability& ability) {

	for (size_t i = 0;i < Abilities->size();++i) {
		if ((*Abilities)[i] == nullptr) {
			(*Abilities)[i] = &ability;
			ability.OnAddToUser(*this);
			return i;
		}
	}
	Abilities->push_back(&ability);
	ability.OnAddToUser(*this);
	return Abilities->size()-1;
}
size_t AbilityUserObject::AddAbility(Ability& ability) {
	if (Abilities == nullptr)
		Abilities = new vector<Ability*>(1);

	if (!CheckAbilityClone(ability.GetCatalogID(),ability.GetSubcatalogID()))
		return SIZE_MAX;

	return AddNewAbilityToArr(ability);
}
size_t AbilityUserObject::AddAbilityFromCatalog(size_t catID, std::byte subCatID) {

	//add abiliity from AbilitiesCatalog
	throw exception("Should be copied from AbilitiesCatalog");
}
bool AbilityUserObject::CheckAbilityClone(size_t catID, std::byte subCatID) const {
	
	for (auto ab : *Abilities) {
		if (ab != nullptr &&
			ab->GetCatalogID() == catID &&
			ab->GetSubcatalogID() == subCatID) {

			return false;
		}
	}
	return true;
}

void AbilityUserObject::RemoveAbilityFromArr(size_t index) {

	if ((*Abilities)[index] == nullptr)
		throw exception("Request to del ability is already null");

	(*Abilities)[index]->OnRemoveFromUser(*this);
	delete (*Abilities)[index];
	(*Abilities)[index] = nullptr;

	for (auto ab : *Abilities) {
		if (ab != nullptr)
			return;
	}

	delete Abilities;
	Abilities = nullptr;
}
void AbilityUserObject::RemoveAbility(Ability& ability) {
	
	if (Abilities == nullptr)
		throw exception("Object hasn't any abilities");

	for (size_t i = 0;i < Abilities->size();++i) {
		if ((*Abilities)[i] == &ability) {
			RemoveAbilityFromArr(i);
		}
	}

	throw exception("Haven't requested ability in array");
}
void AbilityUserObject::RemoveCatalogAbility(size_t catID, std::byte subCatID) {

	if(Abilities==nullptr)
		throw exception("Object hasn't any abilities");

	auto predicate = CatalogObject::Predicate_ByID_n_SubID_ref<Ability>(catID, subCatID);
	auto ability = *CollectionsExts::Get(*Abilities, predicate);

	if (ability == nullptr)
		throw exception("Object hasn't ability with input catalog information");

	Ability* ab = nullptr;

	for (size_t i = 0; i < Abilities->size(); ++i) {
		ab = (*Abilities)[i];
		if (predicate.Condition(ab))
			RemoveAbilityByArrIndex(i);
	}

	throw exception("Haven't requested ability in array");
}
void AbilityUserObject::RemoveAbilityByArrIndex(size_t index) {
	if (Abilities == nullptr)
		throw exception("Object hasn't any abilities");

	if (Abilities->size() <= index)
		throw exception("Index out of range");

	RemoveAbilityFromArr(index);
}

Ability* AbilityUserObject::GetAbility(size_t orderInArr) const {
	if (Abilities == nullptr)
		return nullptr;

	if (orderInArr >= Abilities->size())
		return nullptr;

	return (*Abilities)[orderInArr];
}
vector<Ability*>::iterator AbilityUserObject::GetAbilitiesIter_Begin() const {
	return Abilities->begin();
}
vector<Ability*>::iterator AbilityUserObject::GetAbilitiesIter_End() const {
	return Abilities->end();
}
size_t AbilityUserObject::GetAbilitiesCount() const {
	return Abilities->size();
}
bool AbilityUserObject::HasAbilities() const {
	return Abilities != nullptr;
}