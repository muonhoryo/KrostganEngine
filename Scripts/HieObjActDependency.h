#pragma once

#include <_Events.h>
#include <ValueDependency.h>
#include <GroupSelectionSystem.h>

using namespace KrostganEngine;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;

namespace KrostganEngine::UI {

	class HieObjActDependency : public IUIDependency {

	private:
		struct ChangeFirstChoosenSubsc final : public INoArgsEventSubscriber {

			ChangeFirstChoosenSubsc(HieObjActDependency& Owner)
				:Owner(Owner)
			{}

			void Execute() override {
				Owner.Update();
			}

		private:
			HieObjActDependency& Owner;
		};

		struct ChangeChoosenGroupSubsc final : public IEventSubscriber<pair<size_t, std::byte>> {

			ChangeChoosenGroupSubsc(HieObjActDependency& Owner)
				:Owner(Owner)
			{}

			void Execute(pair<size_t, std::byte>& args) override {
				Owner.Update();
			}

		private:
			HieObjActDependency& Owner;
		};

	protected:
		HieObjActDependency()
			:Subsc_ChangeTar(ChangeFirstChoosenSubsc(*this)),
			Subsc_ChangeTar_Group(ChangeChoosenGroupSubsc(*this)){

			GroupSelectionSystem::ChangeChoosenEntsEvent.Add(Subsc_ChangeTar);
			GroupSelectionSystem::ChangeChoosenGroupEvent.Add(Subsc_ChangeTar_Group);
		}

		virtual ~HieObjActDependency() {

			GroupSelectionSystem::ChangeChoosenEntsEvent.Remove(Subsc_ChangeTar);
			GroupSelectionSystem::ChangeChoosenGroupEvent.Remove(Subsc_ChangeTar_Group);
		}

		friend class ChangeFirstSelSubsc;

	private:
		ChangeFirstChoosenSubsc Subsc_ChangeTar;
		ChangeChoosenGroupSubsc Subsc_ChangeTar_Group;
	};
}