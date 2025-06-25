
#include <BypassVertex.h>
#include <iostream>
#include <Extensions.h>

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
}
BypassWay& BypassVertex::GenerateWay(BypassVertex& secondPnt) {

	BypassWay& way = *new BypassWay(*this, secondPnt);
	AddWay(way);
	secondPnt.AddWay(way);

	cout << "Genearate bypass way from " << ToString(Position) << " to " << ToString(secondPnt.Position) << endl;

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