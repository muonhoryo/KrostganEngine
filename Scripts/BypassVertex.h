#pragma once

#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <_Extensions.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	class BypassWay;

	class BypassVertex final {

	public:
		BypassVertex(Vector2f Position)
			:Position(Position) 
		{
			cout << "Generate bypass vertex: " << to_string(Position) << endl;
		}

		Vector2f GetPosition() const {
			return Position;
		}
		const vector<BypassWay*>& GetWays() const {
			return Ways;
		}

		void AddWay(BypassWay& way);
		BypassWay& GenerateWay(BypassVertex& secondPnt);
		bool CheckWayTo(const BypassVertex& target);

	private:
		Vector2f Position;
		vector<BypassWay*> Ways;
	};

	class BypassWay final {
	public:
		BypassWay(BypassVertex& First, BypassVertex& second);

		BypassVertex& First;
		BypassVertex& Second;
		float Cost;
	};

	struct WaysSorting {
		bool operator()(BypassWay* a, BypassWay* b) const { return a->Cost < b->Cost; }
	};
}