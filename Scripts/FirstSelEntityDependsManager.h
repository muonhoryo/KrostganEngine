#pragma once

#include <ValueDependency.h>
#include <vector>
#include <GroupSelectionSystem.h>
#include <IEntityUIDependency.h>

using namespace std;
using namespace KrostganEngine::Core;
using namespace KrostganEngine::EntitiesControl;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::UI {
	class FirstSelEntityDependsManager : public IUIDependency{
		
	private:
		struct FirstSelChangedEvSubsc : public INoArgsEventSubscriber {

			FirstSelChangedEvSubsc(FirstSelEntityDependsManager& Owner)
				:Owner(Owner)
			{}

			void Execute() override {
				Owner.Update();
			}

		private:
			FirstSelEntityDependsManager& Owner;
		};

	public:
		FirstSelEntityDependsManager(){
			Subsc = new FirstSelChangedEvSubsc(*this);
			GroupSelectionSystem::ChangeSelectablesEvent.Add(*Subsc);
		}
		~FirstSelEntityDependsManager() {
			for (auto depend : Dependencies)
				delete depend;

			GroupSelectionSystem::ChangeSelectablesEvent.Remove(*Subsc);
			delete Subsc;
		}

		void Update() override {
			Entity* newTar = dynamic_cast<Entity*>(GroupSelectionSystem::GetFirstSelectable());
			if (Target != newTar) {
				for (auto depend : Dependencies) {
					depend->ChangeDepTarget(newTar);
				}
			}
		}
		void AddDependency(IEntityUIDependency& dependency) {
			Dependencies.push_back(&dependency);
		}
		void RemoveDependency(IEntityUIDependency& dependency) {
			CollectionsExts::Remove(Dependencies, &dependency);
		}

	private:
		vector<IEntityUIDependency*> Dependencies;
		FirstSelChangedEvSubsc* Subsc;

		Entity* Target=nullptr;
	};
}