#pragma once

#include <Events.h>
#include <HPSystem.h>
#include <ICallbackRec_GraphRen.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {

	class VisualOnDeathDestroyer :IEventSubscriber<ObjectDeathEventArgs> {
	public:
		VisualOnDeathDestroyer(ICallbackRec_GraphRen& Target, IAttackableObj& Owner)
			:Target(&Target),
			Owner(Owner) {
		}
		~VisualOnDeathDestroyer() {}

		void Execute(const ObjectDeathEventArgs& args) override {
			if (Target != nullptr) {

				delete Target;
				Target = nullptr;
			}
		}

	private:
		ICallbackRec_GraphRen* Target;
		IAttackableObj& Owner;
	};
}