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
	class FirstChoosenEntityDependsManager : public IUIDependency{
		
	private:
		struct FirstChoosenChangedEvSub : public INoArgsEventSubscriber {
			
			FirstChoosenChangedEvSub(FirstChoosenEntityDependsManager& Owner)
				:Owner(Owner)
			{}

			void Execute() override {
				Owner.Update();
			}

		private:
			FirstChoosenEntityDependsManager& Owner;
		};

		struct ChoosenGroupChangedEvSub : public IEventSubscriber<pair<size_t,std::byte>>{

			ChoosenGroupChangedEvSub(FirstChoosenEntityDependsManager& Owner)
				:Owner(Owner)
			{}

			void Execute(pair<size_t, std::byte>& args) override {
				Owner.Update();
			}

		private:
			FirstChoosenEntityDependsManager& Owner;
		};

		struct TargetAAStatsChangedEvSubsc : public IEventSubscriber<const int> {

			TargetAAStatsChangedEvSubsc(FirstChoosenEntityDependsManager& Owner)
				:Owner(Owner)
			{}

			void Execute(const int&) override {
				Owner.UpdateByAAStats();
			}

		private:
			FirstChoosenEntityDependsManager& Owner;
		};

	public:
		FirstChoosenEntityDependsManager()
			:Subsc_ChangeTar(FirstChoosenChangedEvSub(*this)),
			Subsc_ChangeTar_ChoiseGroup(ChoosenGroupChangedEvSub(*this)),
			Subsc_ChangeAAStats(TargetAAStatsChangedEvSubsc(*this)){

			GroupSelectionSystem::ChangeChoosenEntsEvent.Add(Subsc_ChangeTar);
			GroupSelectionSystem::ChangeChoosenGroupEvent.Add(Subsc_ChangeTar_ChoiseGroup);
		}
		~FirstChoosenEntityDependsManager() {
			for (auto depend : Dependencies)
				delete depend;

			GroupSelectionSystem::ChangeChoosenEntsEvent.Remove(Subsc_ChangeTar);
			GroupSelectionSystem::ChangeChoosenGroupEvent.Remove(Subsc_ChangeTar_ChoiseGroup);
		}

		void Update() override {
			Entity* newTar = dynamic_cast<Entity*>(GroupSelectionSystem::GetFirstChoosen());
			if (Target != newTar) {

				if (Target != nullptr) {
					Target->GetBattleStats().ChangeCurrAAStatsEvent.Remove(Subsc_ChangeAAStats);
				}

				for (auto depend : Dependencies) {
					depend->ChangeDepTarget(newTar);
				}

				Target = newTar;
				if (Target != nullptr) {
					Target->GetBattleStats().ChangeCurrAAStatsEvent.Add(Subsc_ChangeAAStats);
				}
			}
		}
		void UpdateByAAStats() {

			for (auto depend : Dependencies) {
				depend->ChangeDepTarget(Target);
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
		FirstChoosenChangedEvSub Subsc_ChangeTar;
		ChoosenGroupChangedEvSub Subsc_ChangeTar_ChoiseGroup;
		TargetAAStatsChangedEvSubsc Subsc_ChangeAAStats;

		Entity* Target=nullptr;
	};
}