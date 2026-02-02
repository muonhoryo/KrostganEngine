
#include <BypassVertex.h>
#include <iostream>
#include <_Extensions.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;
using namespace KrostganEngine::Core;

void BypassVertex::AddWay(BypassWay& way) {

	BypassVertex* ref1 = &way.First;
	BypassVertex* ref2 = &way.Second;

	if (ref1!= this && ref2!= this)
		throw exception("The way doesn't contains target vertex");

	Ways.push_back(&way);
	sort(Ways.begin(), Ways.end(), [](BypassWay* first, BypassWay* second) {return first->Cost < second->Cost;});
}
BypassWay& BypassVertex::GenerateWay(BypassVertex& secondPnt) {

	BypassWay& way = *new BypassWay(*this, secondPnt);
	AddWay(way);
	secondPnt.AddWay(way);

	cout << "Genearate bypass way from " << to_string(Position) << " to " << to_string(secondPnt.Position) << endl;

	return way;
}
bool BypassVertex::CheckWayTo(const BypassVertex& target) {
	for (auto& way : Ways) {
		if (&way->First == &target || &way->Second == &target)
			return true;
	}
	return false;
}

BypassWay::BypassWay(BypassVertex& First, BypassVertex& Second) 
	:First(First),
	Second(Second){

	Cost = Length(First.GetPosition() - Second.GetPosition());
}