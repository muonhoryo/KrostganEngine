
#include <Ability_NonTargetable.h>

using namespace KrostganEngine::GameObjects;

Ability_NonTargetable::Ability_NonTargetable(size_t CatalogID, std::byte SubcatalogID)
	:Ability(CatalogID, SubcatalogID) {

}
Ability_NonTargetable::Ability_NonTargetable() {

}
Ability_NonTargetable::~Ability_NonTargetable() {

}

void Ability_NonTargetable::OnAddToUser(AbilityUserObject& user) {
	Owner = &user;
}