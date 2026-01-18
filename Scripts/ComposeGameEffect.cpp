
#include <GameEffectsSystem.h>

using namespace KrostganEngine::GameObjects;

ComposeGameEffect::ComposeGameEffect(size_t CatalogID, std::byte SubcatalogID) 
	:CatalogObject(CatalogID,SubcatalogID){

}
ComposeGameEffect::ComposeGameEffect(const ComposeGameEffect& copy) 
	:CatalogObject(copy.GetCatalogID(),copy.GetSubcatalogID()){

}
ComposeGameEffect::~ComposeGameEffect() {

}

void ComposeGameEffect::Set_IsStackable(bool isStackable) {
	IsStackable = isStackable;
	if (SourcesCount != 0)
		throw exception("Try to change stackability of compose effect");
}

unsigned int ComposeGameEffect::GetSourcesCount() const {
	return SourcesCount;
}
bool ComposeGameEffect::Get_IsStackable() const {
	return IsStackable;
}