
#include <Ability_Aura.h>

using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

Ability_Aura::Ability_Aura(float range, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff, size_t CatalogID, std::byte SubcatalogID)
	:Ability_Passive(CatalogID,SubcatalogID),
		AuraObj(*new Aura(*new CircleCollShape(DEFAULT_POSITION, range) ,Fraction::Neutral,ToTargetRelMask,GameEff)){

}
Ability_Aura::Ability_Aura(float range, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff)
	:AuraObj(*new Aura(*new CircleCollShape(DEFAULT_POSITION, range), Fraction::Neutral, ToTargetRelMask, GameEff)){

}
Ability_Aura::~Ability_Aura() {

	delete& AuraObj;
}

void Ability_Aura::OnAddToUser(AbilityUserObject& user) {
	Owner_Frac = dynamic_cast<IFractionMember*>(&user);
	if (Owner_Frac != nullptr) {
		AuraObj.SetFraction(Owner_Frac->GetFraction());
		AuraObj.CreateToFracMemDependency(*Owner_Frac);
	}
	Owner = &user;
	AuraObj.SetParent(Owner);
	AuraObj.SetGlobalPosition(Owner->GetGlobalPosition());
}
void Ability_Aura::OnRemoveFromUser(AbilityUserObject& user) {

	if (Owner_Frac != nullptr) {
		AuraObj.SetFraction(Fraction::Neutral);
		AuraObj.DestroyToFracMemDependency();
		Owner_Frac = nullptr;
	}
	Owner = nullptr;
	AuraObj.SetParent(nullptr);
	AuraObj.SetGlobalPosition((Vector2f)ITransformableObj::NULL_POS);
}