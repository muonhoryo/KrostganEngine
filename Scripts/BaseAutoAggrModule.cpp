
#include <BaseAutoAggrModule.h>
#include <Engine.h>
#include <Extensions.h>
#include <list>
#include <PathFinding_Diijkstra.h>

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

	if (Target != nullptr)
		delete Target;
}

IAttackableObj* BaseAutoAggrModule::GetCurrTarget() const {
	if (Target == nullptr)
		return nullptr;
	return Target->GetPtr_t();
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

	if (Target == nullptr)
	{
		TurnFindTargetState();
		return;
	}

	auto t_ptr = Target->GetPtr_t();
	if (t_ptr == nullptr ||
		t_ptr->GetHPModule().DeathModule.GetIsDeadState())
	{
		TurnFindTargetState();
		return;
	}

	if (IsAttack) {		//Is there target in owner's attack range

		if (!Owner.GetAAModule().CheckTargetReach()) {	//Target left the range of AA
			//Follow the target and start attacking it
			IsAttack = false;
			ActionMediator.ResetCurrActions();
			float alloDist = Owner.GetBattleStats().GetAARadius();
			ActionMediator.AddAction((IEntityAction*)new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(*Target)));

			if (IsFollowTargets) {

				auto folAct = new EntityAction_FollowObject(Owner, Owner,watch_ptr_handler_wr_c<TransformableObj>(*Target), alloDist);

				ActionMediator.AddAction((IEntityAction*)folAct);

				Segment segm(Owner.GetGlobalPosition(), t_ptr->GetGlobalPosition());
				if (Engine::GetPhysicsEngine().RayHit(segm,
					(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings))) {

					list<Vector2f>* lst = PathFinding_Diijkstra::GetPath(segm.First, segm.Second);
					if (lst != nullptr && lst->size() > 1) {

						typename list<Vector2f>::reverse_iterator beg = lst->rbegin();
						++beg;
						typename list<Vector2f>::reverse_iterator end = lst->rend();

						for (;beg != end;++beg) {

							ActionMediator.AddAction((IEntityAction*)new EntityAction_MoveToPoint(Owner, Owner, *beg));
						}
					}
				}
			}
		}
	}
	else {

		if (Owner.GetAAModule().CheckTargetReach()) {		//Reach the target to AA

			if (ActionMediator.GetActionsCount() == 0) {

				auto aaAct = new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(*Target));
				ActionMediator.AddAction((IEntityAction*)aaAct);
			}
			IsAttack = true;
		}
		else {
			Vector2f pos=Owner.GetGlobalPosition();
			float dist = Length(pos- t_ptr->GetClosestPoint(pos));
			float alloDist = Owner.GetBattleStats().GetAutoAggrRadius();
			if (dist-alloDist> eps) {
				TurnFindTargetState();
			}
		}
	}
}
void BaseAutoAggrModule::FindTarget(CallbackRecArgs_Upd& args) {

	float radius = Owner.GetBattleStats().GetAutoAggrRadius();
	Vector2f pos = Owner.GetGlobalPosition();
	TargsBuffer=Engine::GetPhysicsEngine().OverlapCircle_All(pos, radius, TARGETS_MASK);
	if (TargsBuffer.size() != 0) {		//Has potential targets in auto-aggr radius

		if (Target != nullptr)
			delete Target;

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
				dist = Length(parTar->GetGlobalPosition() - pos);

				if (dist < minDist) {		//Finds nearest target
					TargetTransform = dynamic_cast<TransformableObj*>(parTar);
					if (TargetTransform == nullptr)
						continue;

					auto& t_ptr = parTar->GetPtr();

					Target = new watch_ptr_handler_wr<IAttackableObj>(t_ptr);

					delete &t_ptr;
					minDist = dist;
				}
			}
		}
		if (Target != nullptr) {

			HasTarget = true;
			auto& aaMod = Owner.GetAAModule();
			auto ptr= Target->GetPtr_t();
			aaMod.SetAsTarget(new watch_ptr_handler_wr<IAttackableObj>(*(watch_ptr_handler*)Target));
			ActionMediator.ResetCurrActions();
			if (aaMod.CheckTargetReach(*ptr)) {			//Target is in attack range of executor

				auto aaAct = new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(*Target));
				ActionMediator.AddAction((IEntityAction*)aaAct);
				IsAttack = true;
			}
			else{									//Owner needs to follow target first

				if (IsFollowTargets) {

					float alloDist = Owner.GetBattleStats().GetAARadius();
					auto aaAct_ = new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(*Target));
					auto folAct = new EntityAction_FollowObject(Owner, Owner, watch_ptr_handler_wr_c<TransformableObj>(*Target), alloDist);
					ActionMediator.AddAction((IEntityAction*)aaAct_);
					ActionMediator.AddAction((IEntityAction*)folAct);

					Segment segm(Owner.GetGlobalPosition(), ptr->GetGlobalPosition());
					if (Engine::GetPhysicsEngine().RayHit(segm,
						(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings))) {

						list<Vector2f>* lst = PathFinding_Diijkstra::GetPath(segm.First, segm.Second);
						if (lst != nullptr && lst->size() > 1) {

							typename list<Vector2f>::reverse_iterator beg = lst->rbegin();
							++beg;
							typename list<Vector2f>::reverse_iterator end = lst->rend();

							for (;beg != end;++beg) {

								ActionMediator.AddAction((IEntityAction*)new EntityAction_MoveToPoint(Owner, Owner, *beg));
							}
						}
					}
				}
				IsAttack = false;
			}
		}
	}
}
void BaseAutoAggrModule::TurnFindTargetState() {
	if (Target != nullptr) {

		delete Target;
		Target = nullptr;
	}
	Owner.GetAAModule().SetAsTarget(nullptr);
	HasTarget = false;
	ActionMediator.ResetCurrActions();
}