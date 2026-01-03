
#include <EntityOrder_AttackTarget.h>
#include <Extensions.h>
#include <Engine.h>
#include <EntityAction_AutoAttack.h>
#include <EntityAction_FollowObject.h>
#include <PathFinding_Diijkstra.h>
#include <WarFogObserversManager.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::Core;

EntityOrder_AttackTarget::EntityOrder_AttackTarget(
	OrdersExecutor& Owner,
	WorldTransfObj& OwnerTransform, 
	watch_ptr_handler_wr<IAttackableObj> Target,
	IFractionMember* Target_FracMem,
	EntityBattleStats* Target_BatStats)
		:IEntityOrder(),
		EntityOrder_ImmobilityChecking(OwnerTransform),
			Owner(Owner),
			Target(Target),
			Target_BatStats(Target_BatStats),
			AAModule(Owner.GetAAModule()),
			OnFractionChangedSubs(nullptr){

	if (Target_FracMem != nullptr) {

		OnFractionChangedSubs = new OnFractionChanged(*this, *Target_FracMem);
		IFractionMember::MemberHasChangedFracEvent.Add(*OnFractionChangedSubs);
	}
}
EntityOrder_AttackTarget::~EntityOrder_AttackTarget() {
	if (OnFractionChangedSubs != nullptr) {
		
		IFractionMember::MemberHasChangedFracEvent.Remove(*OnFractionChangedSubs);
		delete OnFractionChangedSubs;
	}
}

bool EntityOrder_AttackTarget::CheckExecCondition() {
	
	if (Owner.GetAAModule().GetCurrAAStats() == nullptr)		//Owner cannot auto-attack now
		return true;

	IAttackableObj* ptr = Target.GetPtr_t();

	if (ptr == nullptr)
		return true;

	if (!ptr->CheckAttackReachability(IAttackableObj::AtkParam::IsAA))
		return true;

	if (!IsTargetObserving())
		return true;

	if (CheckImmobility(ptr->GetGlobalPosition()) && Owner.GetAAModule().GetCurrentTarget() == nullptr)
		return true;

	return false;
}
list<IEntityAction*>* EntityOrder_AttackTarget::GetActions() {

	IAttackableObj* ptr = Target.GetPtr_t();
	if (ptr == nullptr)
		return nullptr;

	list<IEntityAction*>* lst = new list<IEntityAction*>();

	if (Owner.GetAAModule().CheckTargetReach(*ptr)) {			//Target is in attack range of executor

		EntityAction_AutoAttack* act = new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(Target), Target_BatStats);
		lst->push_back((IEntityAction*)act);
	}
	else {									//Owner needs to follow target first

		Segment ray(OwnerTransform.GetGlobalPosition(), ptr->GetGlobalPosition());
		if (Engine::GetPhysicsEngine().RayHit(ray, LevelBypassMapManager::ENTITY_UNPASSABLE_OBJS_LAYER))
		{
			list<Vector2f>* pnts = PathFinding_Diijkstra::GetPath(ray.First, ray.Second);
			if (pnts != nullptr && pnts->size() >1) {

				typename list<Vector2f>::iterator end = pnts->end();
				--end;
				for (auto it = pnts->begin(); it != end;++it) {

					IEntityAction* act = new EntityAction_MoveToPoint(Owner, OwnerTransform, *it);
					lst->push_back(act);
				}
			}
		}
		float alloDist = Owner.GetBattleStats().GetCurrAAStats()->GetRange();
		EntityAction_FollowObject* folAct = new EntityAction_FollowObject(Owner, OwnerTransform, 
			*new watch_ptr_handler_wr_c<WorldTransfObj>(Target),
			alloDist);
		EntityAction_AutoAttack* aaAct = new EntityAction_AutoAttack(Owner, watch_ptr_handler_wr<IAttackableObj>(Target), Target_BatStats);
		lst->push_back((IEntityAction*)folAct);
		lst->push_back((IEntityAction*)aaAct);
	}

	return lst;
}
void EntityOrder_AttackTarget::OnStartExecution() 
{
	Owner.GetAutoAggrModule().TurnOff();
	AAModule.SetAsTarget(new watch_ptr_handler_wr<IAttackableObj>(Target));
}
void EntityOrder_AttackTarget::OnEndExecution() 
{
	Owner.GetAutoAggrModule().TurnOn();
	AAModule.SetAsTarget(nullptr);
}
EntityOrderType EntityOrder_AttackTarget::GetOrderType() {
	return EntityOrderType::AttackTarget;
}

const ITransformableObj* EntityOrder_AttackTarget::GetTarget() const {
	return Target.GetPtr_t_c();
}

bool EntityOrder_AttackTarget::IsTargetObserving() const {

	float stealth = (Target_BatStats == nullptr) ? FLT_MAX : Target_BatStats->GetStealth().Stat;

	return WarFogObserversManager::GetInstance()->Intersect(Target.GetPtr_t_c()->GetGlobalPosition(), Owner.GetFraction(),stealth);
}