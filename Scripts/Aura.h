#pragma once

#include <TriggerZone.h>
#include <_RelationsSystem.h>
#include <GameEffectsSystem.h>

using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {


	class Aura final : public TriggerZone, public virtual IFractionMember {

	//
	// OnFractionChanged-event subscriber
	//

	public:
		/// <summary>
		/// ToOwnerFracDependency is used in cases, where aura is spotted to object 
		/// that has a definitely fraction and which fraction can be changed during game.
		/// 
		/// </summary>
		class ToOwnerFracDependency final : public IEventSubscriber<const IFractionMember::ChangeFractionEvArgs> {

		public:
			ToOwnerFracDependency(Aura& Owner, const IFractionMember& Target)
				:Owner(Owner),
				Target(Target)
			{}

			void Execute(IFractionMember::ChangeFractionEvArgs const& args) override {

				if (&Target == &args.Owner) {

					if (args.OldFraction != args.NewFraction) {

						Owner.SetFraction(args.NewFraction);
					}
				}
			}

		private:
			Aura& Owner;
			const IFractionMember& Target;
		};

	//
	// Aura's class body
	//

	public:
		Aura(ColliderShape& TriggerCollider, FractionWrapper  AuraFrac, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff, WorldTransfObj& Parent);
		Aura(ColliderShape& TriggerCollider, FractionWrapper  AuraFrac, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff);
		virtual ~Aura();

		void SetGlobalScale(Vector2f size) override;
		void SetGlobalPosition(Vector2f pos) override;
		void SetLocalScale(Vector2f scale) override;
		void SetLocalPosition(Vector2f pos) override;

		const ColliderShape& GetCollider() const override;

		FractionWrapper GetFraction()const override;
		void SetFraction(FractionWrapper fraction) override;

		void CreateToFracMemDependency(const IFractionMember& Owner);
		void DestroyToFracMemDependency();

		static inline const PhysicsLayer AURA_PHYSLAYER = (PhysicsLayer)((int)PhysicsLayer::Buildings | (int)PhysicsLayer::Units);

	protected:
		vector<IPhysicalObject*>	OverlapAll() const override;
		bool						EnterTriggerCondition(const IPhysicalObject& inputObj) const override;

		void OnTriggerEnter(IPhysicalObject& obj) override;
		void OnTriggerExit(watch_ptr_handler_wr<IPhysicalObject>& obj) override;

	private:
		ColliderShape& TriggerCollider;

		Relation					ToTargetRelMask;
		ComposeGameEff_Permanent&	GameEff;
		FractionWrapper 			AuraFrac = FractionWrapper();
		ToOwnerFracDependency*		FracDependency = nullptr;

		bool IsEffectedByAura(FractionWrapper  targetFrac) const;
		bool PassNeutral;
		bool IsEffInstant;

	};
}