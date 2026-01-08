#pragma once

#include <AbilitiesSystem.h>
#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class Ability_Directional : public Ability {

	public:
		virtual ~Ability_Directional();

		virtual void Activate(Vector2f targetPos) = 0;

	protected:
		Ability_Directional(size_t CatalogID, std::byte SubcatalogID);
		Ability_Directional();

		void OnAddToUser(AbilityUserObject& user) override;

		AbilityUserObject* Owner = nullptr;
	};
}