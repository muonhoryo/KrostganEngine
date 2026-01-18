#pragma once

#include <Ability_NonTargetable.h>
#include <GameEffectsSystem.h>

namespace KrostganEngine::GameObjects {
	class Ability_NonTar_Durable : public Ability_NonTargetable {

	private:
		struct OnRemoveGameEffEvAction : public IEventSubscriber<const ComposeGameEffect&> {

			OnRemoveGameEffEvAction(Ability_NonTar_Durable& Owner) 
				:Owner(Owner),
				Predicate(CatalogObject::Predicate_ByID_n_SubID_ref<const ComposeGameEffect>(0,(std::byte)0)){

			}
			virtual ~OnRemoveGameEffEvAction()
			{}

			void Execute(const ComposeGameEffect& args) override {
				if (Predicate.Condition(&args)) {
					Owner.Cancel();
				}
			}

			void Update() {
				Predicate = CatalogObject::Predicate_ByID_n_SubID_ref<const ComposeGameEffect>
					(Owner.GameEff.GetCatalogID(), Owner.GameEff.GetSubcatalogID());
			}

		private:
			Ability_NonTar_Durable& Owner;
			CatalogObject::Predicate_ByID_n_SubID_ref<const ComposeGameEffect> Predicate;
		};

	public:
		Ability_NonTar_Durable(const ComposeGameEff_Permanent& GameEff,size_t CatalogID, std::byte SubcatalogID);
		Ability_NonTar_Durable(const ComposeGameEff_Permanent& GameEff);
		virtual ~Ability_NonTar_Durable();

		void Activate() override;

		void Set_CooldownSinceStart(bool CooldownSinceStart);

		bool Get_IsActive() const;
		bool Get_CooldownSinceStart() const;
		
	protected:
		void OnAddToUser(AbilityUserObject& user) override;
		void OnRemoveFromUser(AbilityUserObject& user) override;

	private:
		void Cancel();

		const ComposeGameEff_Permanent& GameEff;
		OnRemoveGameEffEvAction OnRemoveEffAction;

		bool IsActive = false;
		bool CooldownSinceStart = false;
	};
}