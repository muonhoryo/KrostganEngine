#pragma once

#include <forward_list>
#include <string>
#include <GameObjects.h>
#include <Events.h>
#include <LevelLoadingInfo.h>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine {
	namespace Core {

		class UnitsLoadEventAction :public IEventSubscriber< forward_list<UnitObject>> {};
		struct UnitsLoadEventArgs {
			UnitsLoadEventArgs(forward_list<UnitObject>* LoadedUnits);
			forward_list<UnitObject> * LoadedUnits;
		};

		class LevelLoader {
		public:
			static ExecutedEvent<UnitsLoadEventArgs> UnitsLoadEvent;

			static forward_list <UnitObject> LoadedUnits;

			static void LoadLevel(const LevelLoadingInfo& levelInfo);


		private:
			static EventHandler <UnitsLoadEventArgs> UnitsLoadEventHan;
		};
	}
}