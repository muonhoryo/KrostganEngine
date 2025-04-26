#pragma once

#include <forward_list>
#include <string>
#include <CoreGameObjects.h>
#include <Events.h>
#include <LevelLoadingInfo.h>
#include <ICallbackRec_GraphRen.h>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {
	struct UnitsLoadEventArgs {
		UnitsLoadEventArgs(forward_list<UnitObject*>* LoadedUnits);
		forward_list<UnitObject*>* LoadedUnits;
	};
	struct GraphicsLoadEventArgs {
		GraphicsLoadEventArgs(forward_list<ICallbackRec_GraphRen*>* LoadedGraphics);
		forward_list<ICallbackRec_GraphRen*>* LoadedGraphics;
	};

	class UnitsLoadEventAction :public IEventSubscriber<UnitsLoadEventArgs> {};
	class GraphicsLoadEventAction :public IEventSubscriber<GraphicsLoadEventArgs> {};


	class LevelLoader {
	public:
		static ExecutedEvent<UnitsLoadEventArgs> UnitsLoadEvent;
		static ExecutedEvent<GraphicsLoadEventArgs> GraphicsLoadEvent;

		static forward_list <UnitObject*> LoadedUnits;
		static forward_list <ICallbackRec_GraphRen*> LoadedGraphics;

		static void LoadLevel(const LevelLoadingInfo& levelInfo);


	private:
		static EventHandler <UnitsLoadEventArgs> UnitsLoadEventHan;
		static EventHandler<GraphicsLoadEventArgs> GraphicsLoadEventHan;
	};
}