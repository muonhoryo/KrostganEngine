
#include <OrderTargetsVisualizer.h>

using namespace KrostganEngine::UI;

//
// 
//FollOrdTarHandler
//
//

OrderTargetsVisualizer::FollOrdTarHandler::FollOrdTarHandler(OrderTargetsVisualizer& Owner, const TransformableObj& Target, size_t PointIndex)
	:ICallbackRec_Upd(),
	Owner(Owner),
	Target(Target),
	PointIndex(PointIndex){
}
OrderTargetsVisualizer::FollOrdTarHandler::~FollOrdTarHandler() {
}

void OrderTargetsVisualizer::FollOrdTarHandler::Update(CallbackRecArgs_Upd args) {
	Owner.ReplacePoint(PointIndex, Target.GetPosition());
}

//
//
//Subscribers
//
//

OrderTargetsVisualizer::AddOrderSubscriber::AddOrderSubscriber(OrderTargetsVisualizer& Owner) : IEventSubscriber<const IEntityOrder*>(),
	Owner(Owner){
}

void OrderTargetsVisualizer::AddOrderSubscriber::Execute(const IEntityOrder* const& args) {
	Owner.TryAddOrderInList(args);
}

OrderTargetsVisualizer::RemoveOrderSubscriber::RemoveOrderSubscriber (OrderTargetsVisualizer& Owner) : IEventSubscriber<const IEntityOrder*>(),
	Owner(Owner){
}

void OrderTargetsVisualizer::RemoveOrderSubscriber::Execute(const IEntityOrder* const& args) {
	const EntityOrder_GlobalPosTarget* gPosOrd = dynamic_cast<const EntityOrder_GlobalPosTarget*>(args);
	if (gPosOrd != nullptr) {
		Owner.RemovePoint_Forward();
		return;
	}
	const EntityOrder_ObjectTarget* tarOrd = dynamic_cast<const EntityOrder_ObjectTarget*>(args);
	if (tarOrd != nullptr) {
		Owner.RemovePoint_Forward();
	}
}

OrderTargetsVisualizer::ClearOrdsQueueSubscriber::ClearOrdsQueueSubscriber(OrderTargetsVisualizer& Owner) : INoArgsEventSubscriber(),
	Owner(Owner) {
}

void OrderTargetsVisualizer::ClearOrdsQueueSubscriber::Execute() {
	Owner.Clear();
}

//
// 
// OrderTargetVisualizer
// 
//

OrderTargetsVisualizer::OrderTargetsVisualizer(Entity& Owner) 
	:Owner(Owner),
	AddSub(new AddOrderSubscriber(*this)),
	RemSub(new RemoveOrderSubscriber(*this)),
	ClearSub(new ClearOrdsQueueSubscriber(*this)),
	Visual(LinesVisPrimitive(InitializeVisualVector(), Color::Green)) {

	DynPointsHandls.push_front(new FollOrdTarHandler(*this, Owner, 0));
	auto itBeg = Owner.GetOrderQueueIter_Begin();
	auto itEnd = Owner.GetOrderQueueIter_AfterEnd();
	for (;itBeg != itEnd;++itBeg)
	{
		TryAddOrderInList(*itBeg);
	}
	Owner.GetOrderEvent.Add(AddSub);
	Owner.ExecuteOrderEvent.Add(RemSub);
	Owner.ResetOrderListEvent.Add(ClearSub);
}
OrderTargetsVisualizer::~OrderTargetsVisualizer() {
	Owner.GetOrderEvent.Remove(AddSub);
	Owner.ExecuteOrderEvent.Remove(RemSub);
	Owner.ResetOrderListEvent.Remove(ClearSub);
	for (auto fl : DynPointsHandls) {
		delete fl;
	}
}

void OrderTargetsVisualizer::ReplacePoint(size_t pointIndex, Vector2f newPos) {
	Visual.SetPointPosition(newPos, pointIndex);
}

void OrderTargetsVisualizer::TryAddOrderInList(const IEntityOrder* order) {
	const EntityOrder_GlobalPosTarget* gPosOrd = dynamic_cast<const EntityOrder_GlobalPosTarget*>(order);
	if (gPosOrd != nullptr) {
		AddPoint_Back(gPosOrd->TargetGlobalPos);
		return;
	}
	const EntityOrder_ObjectTarget* tarOrd = dynamic_cast<const EntityOrder_ObjectTarget*>(order);
	if (tarOrd != nullptr) {
		AddPoint_Back(tarOrd->GetTarget());
	}
}

void OrderTargetsVisualizer::AddPoint_Back(Vector2f point) {
	Visual.AddPoint(point);
}

void OrderTargetsVisualizer::AddPoint_Back(const TransformableObj& target) {
	Visual.AddPoint(target.GetPosition());
	DynPointsHandls.push_back(new FollOrdTarHandler(*this, target, Visual.GetPointsCount() - 1));
}

void OrderTargetsVisualizer::RemovePoint_Forward() {
	Visual.RemovePointAt(1);
	FollOrdTarHandler* buffer=nullptr;
	auto it = DynPointsHandls.begin();
	auto it2 = DynPointsHandls.begin();
	++it2;
	++it;
	bool isFound = false;
	for (;it2 != DynPointsHandls.cend();++it2) {
		buffer = *it2;
		if (!isFound) {
			if (buffer->PointIndex == 1)
				isFound = true;
			else {
				++it;
			}
		}
		buffer->PointIndex--;
	}
	if (isFound) {
		delete* it;
		DynPointsHandls.erase(it);
	}
}

void OrderTargetsVisualizer::Clear() {
	auto begIt = DynPointsHandls.begin();
	++begIt;
	auto endIt = DynPointsHandls.cend();
	for (;begIt != endIt;++begIt) {
		delete* begIt;
	}
	begIt = DynPointsHandls.begin();
	++begIt;
	DynPointsHandls.erase(begIt, endIt);
}

vector<Vector2f>& OrderTargetsVisualizer::InitializeVisualVector() {
	vector<Vector2f>& vec = *new vector<Vector2f>();
	vec.push_back(Owner.GetPosition());
	return vec;
}

		




