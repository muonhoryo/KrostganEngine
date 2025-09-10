#pragma once

#include <IEntityOrder.h>
#include <SFML/System.hpp>
#include <ITransformableObj.h>

using namespace sf;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::EntitiesControl {
	class EntityOrder_ObjectTarget {
	public:
		virtual const ITransformableObj* GetTarget() const = 0;
		virtual bool CanTargetItself() { return false; }

	protected:
		EntityOrder_ObjectTarget(){}
	};
}