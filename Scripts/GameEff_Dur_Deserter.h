#pragma once

#include <GameEffectsSystem.h>
#include <RelationsSystem.h>
#include <OrdersExecutor.h>

using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {
	class GameEff_Dur_Deserter : public IGameEffect_Durable {
		
	private:
		struct FractionChangedEvSubs : public IEventSubscriber<const IFractionMember::ChangeFractionEvArgs> {

			FractionChangedEvSubs(IFractionMember& Owner, FractionWrapper DesertingFrac)
				:Owner(Owner),
				DesertingFrac(DesertingFrac) {

			}

			void Execute(const IFractionMember::ChangeFractionEvArgs& args) override {
				if (&args.Owner == &Owner) {
					Owner.SetFraction(DesertingFrac);
				}
			}

		private:
			IFractionMember& Owner;
			FractionWrapper DesertingFrac = FractionWrapper();
		};
		struct StatChangedEvSubs : public IEventSubscriber<int> {

			StatChangedEvSubs(GameEff_Dur_Deserter& Owner)
				:Owner(Owner) {

			}

			void Execute(int& args) override {
				if (args == (int)EntityBattleStatType::Resistance_MindAtt) {

					auto castTar = dynamic_cast<OrdersExecutor*>(Owner.Target);
					if (castTar->GetBattleStats().GetResistance_MindAtt() >= 1) {
						Owner.RemoveEff(*Owner.Target);
					}
				}
			}

		private:
			GameEff_Dur_Deserter& Owner;
		};

	public:
		GameEff_Dur_Deserter(FractionWrapper DesertingFrac);
		GameEff_Dur_Deserter(const GameEff_Dur_Deserter& copy);
		virtual ~GameEff_Dur_Deserter();

		IGameEffect& Clone() const override;

		void SetOwnedEffect(ComposeGameEff_Permanent& ownedEffect);

	protected:
		void Activate(IGameEffTarget& target) override;
		void Deactivate(IGameEffTarget& target) override;

	private:
		void RemoveEff(IGameEffTarget& target);
		/// <summary>
		/// Return true if resistance is too weak to block the game effect
		/// </summary>
		/// <param name="target"></param>
		/// <returns></returns>
		bool CheckResistance(OrdersExecutor& target) const;

		FractionWrapper DesertingFrac = FractionWrapper();
		FractionWrapper OriginFrac = FractionWrapper();
		size_t OwnedEff_CatID = 0;
		std::byte OwnedEff_SubcatID = (std::byte)0;
		IGameEffTarget* Target = nullptr;

		FractionChangedEvSubs* FracChangedSubs = nullptr;
		StatChangedEvSubs StatChangedSubs;


	};
}