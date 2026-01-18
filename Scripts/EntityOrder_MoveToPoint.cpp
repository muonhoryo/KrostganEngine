
#include <EntityOrder_MoveToPoint.h>
#include <EntityAction_MoveToPoint.h>
#include <Extensions.h>
#include <PathFinding_Diijkstra.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_MoveToPoint::EntityOrder_MoveToPoint
		(OrdersExecutor& Owner, 
		Vector2f TargetGlobalCoord,
		float ToTargetMinDistance)
	:EntityOrder_GlobalPosTarget(TargetGlobalCoord),
	EntityOrder_ImmobilityChecking(Owner),
		Owner					(Owner),
		ToTargetMinDistance_Sqr	(ToTargetMinDistance * ToTargetMinDistance){

}

bool EntityOrder_MoveToPoint::CheckExecCondition() {
	float dist = SquareLength(TargetGlobalPos - Owner.GetGlobalPosition());
	return dist <= ToTargetMinDistance_Sqr || CheckImmobility(dist);
}
list <IEntityAction*>* EntityOrder_MoveToPoint::GetActions() {

	list<IEntityAction*>* lst = new list<IEntityAction*>();

	Segment ray(Owner.GetGlobalPosition(), TargetGlobalPos);
	if (Engine::GetPhysicsEngine().RayHit(ray, LevelBypassMapManager::ENTITY_UNPASSABLE_OBJS_LAYER))
	{
		list<Vector2f>* pnts = PathFinding_Diijkstra::GetPath(ray.First, ray.Second);
		if (pnts == nullptr || pnts->size() == 0) {

			IEntityAction* act = new EntityAction_MoveToPoint(Owner, TargetGlobalPos);
			lst->push_back(act);
		}
		else {
			for (Vector2f pnt : *pnts) {

				IEntityAction* act = new EntityAction_MoveToPoint(Owner, pnt);
				lst->push_back(act);
			}
		}
	}
	else {

		IEntityAction* act = new EntityAction_MoveToPoint(Owner, TargetGlobalPos);
		lst->push_back(act);
	}
	return lst;
}
void EntityOrder_MoveToPoint::OnStartExecution()
{
	Owner.GetAutoAggrModule().TurnOff();
}
void EntityOrder_MoveToPoint::OnEndExecution() 
{
	Owner.GetAutoAggrModule().TurnOn();
}
EntityOrderType EntityOrder_MoveToPoint::GetOrderType() {
	return EntityOrderType::MovingToPoint;
}