#pragma once

#include <GameEffectsSystem.h>

namespace KrostganEngine::GameObjects {
	class GameEff_Inst_AddDurEff : public IGameEffect_Instant {

	public:
		GameEff_Inst_AddDurEff(size_t AddedGameEff_CatalogID, std::byte	AddedGameEff_SubcatalogID);
		GameEff_Inst_AddDurEff(const GameEff_Inst_AddDurEff& copy);
		virtual ~GameEff_Inst_AddDurEff();

		IGameEffect& Clone() const override;

	protected:
		void Activate(IGameEffTarget& target) override;

	private:
		size_t		AddedGameEff_CatalogID;
		std::byte	AddedGameEff_SubcatalogID;
	};
}