#pragma once

#include <Events.h>
#include <HPSystem.h>
#include <ICallbackRec_GraphPostRen.h>
#include <ICallbackRec_GraphRen.h>

using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {

	template<typename TTargetType>
	class VisualOnDeathDestroyer :IEventSubscriber<ObjectDeathEventArgs> {
	public:
		VisualOnDeathDestroyer(TTargetType& Target, IAttackableObj& Owner)
			:Target(&Target),
			Owner(Owner) {
		}
		~VisualOnDeathDestroyer() {}

		void Execute(const ObjectDeathEventArgs& args) override {
			if (Target != nullptr) {

				delete Target;
				Target = nullptr;
				//Owner.GetHPModule().DeathModule.DeathEvent.Remove(this);
				//delete this;
			}
		}

	private:
		TTargetType* Target;
		IAttackableObj& Owner;
	};

	class VisualOnDeathDestroyer_PostRen :VisualOnDeathDestroyer<ICallbackRec_GraphPostRen>{
	public:
		VisualOnDeathDestroyer_PostRen(ICallbackRec_GraphPostRen& Target, IAttackableObj& Owner)
			:VisualOnDeathDestroyer(Target, Owner){}
	};
	class VisualOnDeathDestroyer_Ren :VisualOnDeathDestroyer<ICallbackRec_GraphRen> {
	public:
		VisualOnDeathDestroyer_Ren(ICallbackRec_GraphRen& Target, IAttackableObj& Owner)
			:VisualOnDeathDestroyer(Target, Owner) {}
	};
}