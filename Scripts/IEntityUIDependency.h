#pragma once

#include <Entity.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class IEntityUIDependency {

	public:
		virtual void ChangeDepTarget(Entity* target) = 0;

	protected:
		IEntityUIDependency(){}
	};
}