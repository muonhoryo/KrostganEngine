#pragma once

#include <AbilitiesSystem.h>

namespace KrostganEngine::GameObjects {
	class Ability_Passive : public Ability{
	
	public:
		virtual ~Ability_Passive();
	
	protected:
		Ability_Passive(size_t CatalogID, std::byte SubcatalogID);
		Ability_Passive();
	};
}