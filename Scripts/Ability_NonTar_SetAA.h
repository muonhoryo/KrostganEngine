#pragma once

#include <Ability_NonTargetable.h>
#include <GameEffectsSystem.h>

namespace KrostganEngine::GameObjects {

	class Ability_NonTar_SetAA : public Ability_NonTargetable {

	public:
		Ability_NonTar_SetAA(Ability_NonTar_SetAA& NextAbility, size_t AAIndex, size_t CatalogID, std::byte SubcatalogID);
		Ability_NonTar_SetAA(Ability_NonTar_SetAA& NextAbility, size_t AAIndex);
		Ability_NonTar_SetAA(size_t AAIndex, size_t CatalogID, std::byte SubcatalogID);
		Ability_NonTar_SetAA(size_t AAIndex);
		virtual ~Ability_NonTar_SetAA();

		void Activate() override;

		void Set_NextAbility(Ability_NonTar_SetAA& NextAbility);

		void Set_OnAddingAbilityGameEff	(const ComposeGameEffect* OnAddingAbilityGameEff);
		void Set_NextAbilityCooldown	(float NextAbilityCooldown);
		void Set_DeleteGameEffOnRemove	(bool DeleteGameEffOnRemove);

		const ComposeGameEffect*	Get_OnAddingAbilityGameEff() const;
		float						Get_NextAbilityCooldown() const;
		bool						Get_DeleteGameEffOnRemove() const;

	protected:
		void OnAddToUser		(AbilityUserObject& user) override;
		void OnRemoveFromUser	(AbilityUserObject& user) override;

	private:
		Ability_NonTar_SetAA* NextAbility = nullptr;
		size_t AAIndex;

		const ComposeGameEffect* OnAddingAbilityGameEff = nullptr;
		/// <summary>
		/// Cooldown which will set to next ability on activating current
		/// </summary>
		float NextAbilityCooldown = 0;
		bool DeleteGameEffOnRemove = true;
	};
}