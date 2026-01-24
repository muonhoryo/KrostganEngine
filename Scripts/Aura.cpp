
#include <Aura.h>
#include <Engine.h>

using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;

Aura::Aura(ColliderShape& TriggerCollider, Fraction AuraFrac, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff, WorldTransfObj& Parent)
	:TriggerZone(*new Transformable(),Parent),
		TriggerCollider(TriggerCollider),
		AuraFrac(AuraFrac),
		ToTargetRelMask(ToTargetRelMask),
		GameEff(GameEff),
		PassNeutral(IsEffectedByAura(Fraction::Neutral)),
		IsEffInstant(dynamic_cast<ComposeGameEff_Instant*>(&GameEff)!=nullptr){

	TriggerCollider.SetCenter(GetGlobalPosition());
}
Aura::Aura(ColliderShape& TriggerCollider, Fraction AuraFrac, Relation ToTargetRelMask, ComposeGameEff_Permanent& GameEff)
	:TriggerZone(*new Transformable()),
		TriggerCollider(TriggerCollider),
		AuraFrac(AuraFrac),
		ToTargetRelMask(ToTargetRelMask),
		GameEff(GameEff),
		PassNeutral(IsEffectedByAura(Fraction::Neutral)),
		IsEffInstant(dynamic_cast<ComposeGameEff_Instant*>(&GameEff) != nullptr) {

	TriggerCollider.SetCenter(GetGlobalPosition());
}
Aura::~Aura() {

	if (FracDependency != nullptr) {
		IFractionMember::MemberHasChangedFracEvent.Remove(*FracDependency);
		delete FracDependency;
	}
	ClearTriggerList();

	delete& TriggerCollider;
}

void Aura::SetGlobalScale(Vector2f  scale) {
	float oldScale = GetGlobalScale_Sng();
	WorldTransfObj::SetGlobalScale(scale);
	TriggerCollider.Resize(oldScale * GetGlobalScale_Sng());
}
void Aura::SetGlobalPosition(Vector2f pos) {
	WorldTransfObj::SetGlobalPosition(pos);
	TriggerCollider.SetCenter(pos);
}
void Aura::SetLocalScale(Vector2f scale) {
	float oldScale = GetGlobalScale_Sng();
	WorldTransfObj::SetLocalScale(scale);
	TriggerCollider.Resize(oldScale * GetGlobalScale_Sng());
}
void Aura::SetLocalPosition(Vector2f pos) {
	WorldTransfObj::SetLocalPosition(pos);
	TriggerCollider.SetCenter(GetGlobalPosition());
}
const ColliderShape& Aura::GetCollider() const {
	return TriggerCollider;
}
Fraction Aura::GetFraction()const {
	return AuraFrac;
}
void Aura::SetFraction(Fraction fraction) {

	AuraFrac = fraction;
	RecalculateEnteredObjs();
}
void Aura::CreateToFracMemDependency(const IFractionMember& Owner) {
	if (FracDependency == nullptr) {
		FracDependency = new ToOwnerFracDependency(*this, Owner);
		IFractionMember::MemberHasChangedFracEvent.Add(*FracDependency);
	}
}
void Aura::DestroyToFracMemDependency() {

	if (FracDependency != nullptr) {
		IFractionMember::MemberHasChangedFracEvent.Remove(*FracDependency);
		delete FracDependency;
		FracDependency = nullptr;
	}
}

vector<IPhysicalObject*>	Aura::OverlapAll() const {
	return Engine::GetPhysicsEngine().OverlapDynamic_All(TriggerCollider, AURA_PHYSLAYER);
}

bool Aura::EnterTriggerCondition(const IPhysicalObject& inputObj) const {

	auto gefTar = dynamic_cast<const IGameEffTarget*>(&inputObj);
	if (gefTar != nullptr) {

		auto frMemTar = dynamic_cast<const IFractionMember*>(&inputObj);
		if (frMemTar == nullptr) {

			return PassNeutral;
		}
		else {

			return IsEffectedByAura(frMemTar->GetFraction());
		}
	}
	else
		return false;
}
bool Aura::IsEffectedByAura(Fraction targetFrac) const {
	
	return ((int)FractionsSystem::GetRelation(targetFrac, AuraFrac) & (int)ToTargetRelMask) != 0;
}


void Aura::OnTriggerEnter(IPhysicalObject& obj) {
	auto geffTar = dynamic_cast<IGameEffTarget*>(&obj);
	geffTar->AddGameEff(GameEff.Clone());
}
void Aura::OnTriggerExit(watch_ptr_handler_wr<IPhysicalObject>& obj) {
	if (!IsEffInstant) {

		auto ptr = obj.GetPtr_t();
		if (ptr != nullptr) {
			
			auto geffTar = dynamic_cast<IGameEffTarget*>(ptr);
			geffTar->RemoveGameEff(GameEff);
		}
	}
}