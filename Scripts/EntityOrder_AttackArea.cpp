
#include <EntityOrder_AttackArea.h>
#include <EntityAction_MoveToPoint.h>
#include <Extensions.h>
#include <PathFinding_Diijkstra.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_AttackArea::EntityOrder_AttackArea(
	OrdersExecutor&		Owner, 
	WorldTransfObj&		OwnerTransform, 
	Vector2f			TargetGlobalCoord,
	float				ToTargetMinDistance) 
	:EntityOrder_GlobalPosTarget(TargetGlobalCoord),
	EntityOrder_ImmobilityChecking(OwnerTransform),
		Owner(Owner),
		ToTargetMinDistance_Sqr(ToTargetMinDistance * ToTargetMinDistance){
}

bool EntityOrder_AttackArea::CheckExecCondition() {

	if (Owner.GetAAModule().GetCurrAAStats() == nullptr) {	
		
		//Replace AttackArea-order with MoveToPoint-order
		auto newOrder = new EntityOrder_MoveToPoint(Owner, OwnerTransform, TargetGlobalPos, sqrtf(ToTargetMinDistance_Sqr));
		Owner.TryInsertOrder(*newOrder, 1);
		return true;
	}		//Owner cannot auto-attack for now

	float dist = SquareLength(TargetGlobalPos - OwnerTransform.GetGlobalPosition());
	return dist <= ToTargetMinDistance_Sqr || CheckImmobility(dist);
}
list <IEntityAction*>* EntityOrder_AttackArea::GetActions() {

	list<IEntityAction*>* lst = new list<IEntityAction*>();

	Segment ray(OwnerTransform.GetGlobalPosition(), TargetGlobalPos);
	if (Engine::GetPhysicsEngine().RayHit(ray,
		(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings)))
	{
		list<Vector2f>* pnts= PathFinding_Diijkstra::GetPath(ray.First, ray.Second);
		if (pnts == nullptr || pnts->size() == 0) {

			IEntityAction* act = new EntityAction_MoveToPoint(Owner, OwnerTransform, TargetGlobalPos);
			lst->push_back(act);
		}
		else {
			for (Vector2f pnt : *pnts) {

				IEntityAction* act = new EntityAction_MoveToPoint(Owner, OwnerTransform, pnt);
				lst->push_back(act);
			}
		}
	}
	else {

		IEntityAction* act = new EntityAction_MoveToPoint(Owner, OwnerTransform, TargetGlobalPos);
		lst->push_back(act);
	}
	return lst;
}
EntityOrderType EntityOrder_AttackArea::GetOrderType() {
	return EntityOrderType::AttackArea;
}

void EntityOrder_AttackArea::OnStartExecution() {
}
void EntityOrder_AttackArea::OnEndExecution() {

}