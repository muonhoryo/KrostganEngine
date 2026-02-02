#pragma once

#include <_VisualEffectsCore.h>
#include <SFML/Graphics.hpp>

using namespace sf;

namespace KrostganEngine::Visual {
	class IColoredObject : virtual public EffectObject {

	public:
		virtual ~IColoredObject() {}

		virtual Color	GetColor() const = 0;
		virtual void	SetColor(Color color) = 0;

	protected:
		IColoredObject() : EffectObject() {}

	};
}