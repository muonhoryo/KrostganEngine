#pragma once

#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::GameObjects {
	class IStepTracingObj {

	public:
		virtual ~IStepTracingObj(){}

		virtual Vector2f GetPrevMovStep() const = 0;

	protected:
		IStepTracingObj(){}
	};
}