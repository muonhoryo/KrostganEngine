#pragma once

#include <Entity.h>
#include <IModifiableStatsWrapper.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {

	class GetEntStatsWrapperFunc {

	public:
		virtual IModifiableStatsWrapper* GetStatsWrapper(Entity* entity) const = 0;

	protected:
		GetEntStatsWrapperFunc() {}
	};
}