#pragma once

#include <SFML/System.hpp>

using namespace sf;

namespace KrostganEngine::Physics {
	struct Ray {
		Ray(Vector2f Origin, Vector2f Direction)
			:Origin(Origin),
			Direction(Direction){
		}

		Vector2f Origin;
		Vector2f Direction;
	};
	struct Segment {
		Segment(Vector2f First,Vector2f Second)
			:First(First),
			Second(Second){}

		Vector2f First;
		Vector2f Second;
	};
}