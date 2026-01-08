
#include <Ability_Directional.h>

using namespace KrostganEngine::GameObjects;

Ability_Directional::Ability_Directional(size_t CatalogID, std::byte SubcatalogID)
	:Ability(CatalogID, SubcatalogID) {

}
Ability_Directional::Ability_Directional() {

}
Ability_Directional::~Ability_Directional() {

}
	
void Ability_Directional::OnAddToUser(AbilityUserObject& user) {
	Owner = &user;
}