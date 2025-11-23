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

		struct TargetAAStatsChangedEvSubsc : public IEventSubscriber<const int> {

			TargetAAStatsChangedEvSubsc(FirstSelEntityDependsManager& Owner)
				:Owner(Owner)
			{}

			void Execute(const int&) override {
				Owner.UpdateByAAStats();
			}

		private:
			FirstSelEntityDependsManager& Owner;
		};

	public:
		FirstSelEntityDependsManager()
			:Subsc_ChangeTar(FirstSelChangedEvSubsc(*this)),
			Subsc_ChangeAAStats(TargetAAStatsChangedEvSubsc(*this)){

			GroupSelectionSystem::ChangeSelectablesEvent.Add(Subsc_ChangeTar);
		}
		~FirstSelEntityDependsManager() {
			for (auto depend : Dependencies)
				delete depend;

			GroupSelectionSystem::ChangeSelectablesEvent.Remove(Subsc_ChangeTar);
		}

		void Update() override {
			Entity* newTar = dynamic_cast<Entity*>(GroupSelectionSystem::GetFirstSelectable());
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
		FirstSelChangedEvSubsc Subsc_ChangeTar;
		TargetAAStatsChangedEvSubsc Subsc_ChangeAAStats;

		Entity* Target=nullptr;
	};
}