#pragma once

#include <Events.h>
#include <ValueDependency.h>
#include <GroupSelectionSystem.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::UI {

	class HieObjActDependency : public IUIDependency {

	private:
		class ChangeFirstSelSubsc final : public INoArgsEventSubscriber {

		public:
			ChangeFirstSelSubsc(HieObjActDependency& Owner)
				:Owner(Owner)
			{}

			void Execute() override {
				Owner.Update();
			}

		private:
			HieObjActDependency& Owner;
		};

		ChangeFirstSelSubsc Subsc_ChangeTar;

	protected:
		HieObjActDependency()
			:Subsc_ChangeTar(ChangeFirstSelSubsc(*this)){

			GroupSelectionSystem::ChangeSelectablesEvent.Add(Subsc_ChangeTar);
		}

		virtual ~HieObjActDependency() {

			GroupSelectionSystem::ChangeSelectablesEvent.Remove(Subsc_ChangeTar);
		}

		friend class ChangeFirstSelSubsc;
	};
}