#pragma once

#include <TriggerZone.h>
#include <RelationsSystem.h>
#include <GameEffectsSystem.h>

using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::GameObjects {

	class Aura final : public TriggerZone, public virtual IFractionMember {

	public:
		Aura(float auraRange, Fraction AuraFrac, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff, WorldTransfObj& Parent);
		Aura(float auraRange, Fraction AuraFrac, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff);
		virtual ~Aura();

		void SetGlobalScale(Vector2f size) override;
		void SetGlobalPosition(Vector2f pos) override;
		void SetLocalScale(Vector2f scale) override;
		void SetLocalPosition(Vector2f pos) override;

		const ColliderShape& GetCollider() const override;

		Fraction GetFraction()const override;
		void SetFraction(Fraction fraction) override;

		static inline const PhysicsLayer AURA_PHYSLAYER = (PhysicsLayer)((int)PhysicsLayer::Buildings | (int)PhysicsLayer::Units);

	protected:
		vector<IPhysicalObject*>	OverlapAll() const override;
		bool						EnterTriggerCondition(const IPhysicalObject& inputObj) const override;

		void OnTriggerEnter(IPhysicalObject& obj) override;
		void OnTriggerExit(watch_ptr_handler_wr<IPhysicalObject>& obj) override;

	private:
		CircleCollShape TriggerCollider;

		Relation					ToTargetRelMask;
		ComposeGameEff_Permanent&	GameEff;
		Fraction					AuraFrac;

		bool IsEffectedByAura(Fraction targetFrac) const;
		bool PassNeutral;
		bool IsEffInstant;
	};
}