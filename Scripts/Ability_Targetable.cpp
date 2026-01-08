
#include <Ability_Targetable.h>

using namespace KrostganEngine::GameObjects;

Ability_Targetable::Ability_Targetable(size_t CatalogID, std::byte SubcatalogID) 
	:Ability(CatalogID, SubcatalogID) {

}
Ability_Targetable::Ability_Targetable() {

}
Ability_Targetable::~Ability_Targetable() {

}

void Ability_Targetable::OnAddToUser(AbilityUserObject& user) {
	Owner = &user;
}