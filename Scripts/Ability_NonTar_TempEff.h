#pragma once

#include <Ability_NonTargetable.h>
#include <GameEffectsSystem.h>

namespace KrostganEngine::GameObjects {

	class Ability_NonTar_TempEff : public Ability_NonTargetable {

	public:
		Ability_NonTar_TempEff(ComposeGameEff_Temporal& GameEff, float EffDuration, size_t CatalogID, std::byte SubcatalogID);
		Ability_NonTar_TempEff(ComposeGameEff_Temporal& GameEff, float EffDuration);
		virtual ~Ability_NonTar_TempEff();

		void Activate() override;

	private:
		ComposeGameEff_Temporal& GameEff;
		float EffDuration;
	};
}