#pragma once

#include <AbilitiesSystem.h>

namespace KrostganEngine::GameObjects {
	class Ability_NonTargetable : public Ability {

	public:
		virtual ~Ability_NonTargetable();

		virtual void Activate() = 0;

	protected:
		Ability_NonTargetable(size_t CatalogID, std::byte SubcatalogID);
		Ability_NonTargetable();

		void OnAddToUser(AbilityUserObject& user) override;

		AbilityUserObject* Owner = nullptr;
	};
}