#pragma once

#include <Ability_Passive.h>
#include <Aura.h>

using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {
	class Ability_Aura : public Ability_Passive {

	public:
		Ability_Aura(float range, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff, size_t CatalogID, std::byte SubcatalogID);
		Ability_Aura(float range, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff);
		virtual ~Ability_Aura();

	protected:
		void OnAddToUser(AbilityUserObject& user) override;
		void OnRemoveFromUser(AbilityUserObject& user) override;

	private:
		Aura& AuraObj;
		IFractionMember*	Owner_Frac = nullptr;
		AbilityUserObject*	Owner = nullptr;
	};
}