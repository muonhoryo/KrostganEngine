
#include <EntityOrder_MoveToPoint.h>
#include <EntityAction_MoveToPoint.h>
#include <Extensions.h>
#include <Engine.h>
#include <PathFinding_Diijkstra.h>

using namespace sf;
using namespace KrostganEngine;
using namespace KrostganEngine::GameObjects;
using namespace KrostganEngine::EntitiesControl;

EntityOrder_MoveToPoint::EntityOrder_MoveToPoint
		(OrdersExecutor& Owner, 
		TransformableObj& OwnerTransform,
		Vector2f TargetGlobalCoord,
		float ToTargetMinDistance)
	:EntityOrder_GlobalPosTarget(TargetGlobalCoord),
	Owner				(Owner),
	OwnerTransform		(OwnerTransform),
	ToTargetMinDistance	(ToTargetMinDistance){

}

bool EntityOrder_MoveToPoint::CheckExecCondition() {
	float dist = Length(TargetGlobalPos - OwnerTransform.GetGlobalPosition())-ToTargetMinDistance;
	return dist <= eps;
}
list <IEntityAction*>* EntityOrder_MoveToPoint::GetActions() {

	list<IEntityAction*>* lst = new list<IEntityAction*>();

	Segment ray(OwnerTransform.GetGlobalPosition(), TargetGlobalPos);
	if (Engine::GetPhysicsEngine().RayHit(ray,
		(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings)))
	{
		list<Vector2f>* pnts = PathFinding_Diijkstra::GetPath(ray.First, ray.Second);
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