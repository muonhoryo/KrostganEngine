
#include <BaseAutoAggrModule.h>
#include <Engine.h>
#include <Extensions.h>
#include <list>

using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Physics;

BaseAutoAggrModule::BaseAutoAggrModule(Entity& Owner,ExecutorActionsMediator& ActionMediator) 
	: AutoAggressionModule(ActionMediator,Owner.StartExecOrderEvent),
	Target(nullptr),
	TargetTransform(nullptr),
	Owner(Owner),
	HasTarget(false),
	IsAttack(false){

}
BaseAutoAggrModule::~BaseAutoAggrModule() {

}

IAttackableObj& BaseAutoAggrModule::GetCurrTarget() const {
	return *Target;
}

void BaseAutoAggrModule::TurnOnAction() {
	TurnFindTargetState();
	AutoAggressionModule::TurnOnAction();
}
void BaseAutoAggrModule::TurnOffAction() {
	ActionMediator.ResetCurrActions();
	AutoAggressionModule::TurnOffAction();
}

void BaseAutoAggrModule::UpdateAction(CallbackRecArgs_Upd& args) {
	if (HasTarget) {
		CheckCurrTarget(args);
	}
	else {
		FindTarget(args);
	}
}

void BaseAutoAggrModule::CheckCurrTarget(CallbackRecArgs_Upd& args) {
	if (Target->GetHPModule().GetIsDeadState()) {

		TurnFindTargetState();
		return;
	}
	if (IsAttack) {		//Is there target in owner's attack range

		if (!Owner.GetAAModule().CheckTargetReach()) {	//Target left the range of AA
			//Follow the target and start attacking it
			IsAttack = false;
			ActionMediator.ResetCurrActions();
			float alloDist = Owner.GetBattleStats().GetAARadius();
			ActionMediator.AddAction((IEntityAction*)new EntityAction_AutoAttack(Owner, *Target));

			if (IsFollowTargets) {

				ActionMediator.AddAction((IEntityAction*)new EntityAction_FollowObject(Owner, Owner, Target->GetTransform(), alloDist));
			}
		}
	}
	else {

		if (Owner.GetAAModule().CheckTargetReach()) {		//Reach the target to AA
			IsAttack = true;
		}
		else {
			Vector2f pos=Owner.GetPosition();
			float dist = Length(pos- Target->GetClosestPoint(pos));
			float alloDist = Owner.GetBattleStats().GetAutoAggrRadius();
			if (dist-alloDist> eps) {
				TurnFindTargetState();
			}
		}
	}
}
void BaseAutoAggrModule::FindTarget(CallbackRecArgs_Upd& args) {
	float radius = Owner.GetBattleStats().GetAutoAggrRadius();
	Vector2f pos = Owner.GetPosition();
	TargsBuffer=Engine::GetPhysicsEngine().OverlapCircle_All(pos, radius, TARGETS_MASK);
	if (TargsBuffer.size() != 0) {
		Target = nullptr;
		float minDist = FLT_MAX;
		IAttackableObj* parTar = nullptr;
		IFractionMember* memParTar = nullptr;
		float dist=0;
		Relation relat=Relation::Neutral;
		for (auto obj : TargsBuffer) {

			if (obj == &Owner)
				continue;
			memParTar = dynamic_cast<IFractionMember*>(obj);
			parTar = dynamic_cast<IAttackableObj*>(obj);
			if (parTar != nullptr && memParTar!=nullptr) {		//Check that object is can be attacked enemy

				relat = FractionsSystem::GetRelation(Owner.GetFraction(), memParTar->GetFraction());
				if (relat != Relation::Enemy)
					continue;
				dist = Length(parTar->GetTransform().GetPosition() - pos);
				if (dist < minDist) {
					TargetTransform = dynamic_cast<TransformableObj*>(parTar);
					if (TargetTransform == nullptr)
						continue;
					Target = parTar;
					minDist = dist;
				}
			}
		}
		if (Target != nullptr) {
			HasTarget = true;
			auto& aaMod = Owner.GetAAModule();
			aaMod.SetAsTarget(Target);
			ActionMediator.ResetCurrActions();
			if (aaMod.CheckTargetReach(*Target)) {			//Target is in attack range of executor

				ActionMediator.AddAction((IEntityAction*)new EntityAction_AutoAttack(Owner , *Target));
				IsAttack = true;
			}
			else{									//Owner needs to follow target first

				if (IsFollowTargets) {

					float alloDist = Owner.GetBattleStats().GetAARadius();
					ActionMediator.AddAction((IEntityAction*)new EntityAction_AutoAttack(Owner, *Target));
					ActionMediator.AddAction((IEntityAction*)new EntityAction_FollowObject(Owner, Owner, Target->GetTransform(), alloDist));
				}
				IsAttack = false;
			}
		}
	}
}
void BaseAutoAggrModule::TurnFindTargetState() {
	Target = nullptr;
	Owner.GetAAModule().SetAsTarget(nullptr);
	HasTarget = false;
	ActionMediator.ResetCurrActions();
}