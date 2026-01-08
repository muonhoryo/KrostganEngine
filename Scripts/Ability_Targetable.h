#pragma once

#include <AbilitiesSystem.h>
#include <WorldTransfObj.h>

namespace KrostganEngine::GameObjects {
	class Ability_Targetable : public Ability {

	public:
		virtual ~Ability_Targetable();

		virtual void Activate(WorldTransfObj& target) = 0;

	protected:
		Ability_Targetable(size_t CatalogID, std::byte SubcatalogID);
		Ability_Targetable();

		void OnAddToUser(AbilityUserObject& user) override;

		AbilityUserObject* Owner = nullptr;
	};
}