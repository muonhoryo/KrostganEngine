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
}