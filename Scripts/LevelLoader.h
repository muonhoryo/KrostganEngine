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
	struct WallsLoadEventArgs {
		WallsLoadEventArgs(forward_list<WallObject*>* LoadedWalls);
		forward_list<WallObject*>* LoadedWalls;
	};
	struct GraphicsLoadEventArgs {
		GraphicsLoadEventArgs(forward_list<ICallbackRec_GraphRen*>* LoadedGraphics);
		forward_list<ICallbackRec_GraphRen*>* LoadedGraphics;
	};

	class UnitsLoadEventAction :public IEventSubscriber<UnitsLoadEventArgs> {};
	class WallsLoadEventAction:public IEventSubscriber<WallsLoadEventArgs>{};
	class GraphicsLoadEventAction :public IEventSubscriber<GraphicsLoadEventArgs> {};


	class LevelLoader {
	public:
		static inline ExecutedEvent<UnitsLoadEventArgs> UnitsLoadEvent = ExecutedEvent<UnitsLoadEventArgs>();
		static inline ExecutedEvent<WallsLoadEventArgs> WallsLoadEvent=ExecutedEvent<WallsLoadEventArgs>();
		static inline ExecutedEvent<GraphicsLoadEventArgs> GraphicsLoadEvent = ExecutedEvent<GraphicsLoadEventArgs>();

		static inline forward_list<UnitObject*> LoadedUnits= forward_list<UnitObject*>();
		static inline forward_list <WallObject*> LoadedWalls = forward_list<WallObject*>();
		static inline forward_list <ICallbackRec_GraphRen*> LoadedGraphics= forward_list<ICallbackRec_GraphRen*>();

		static void LoadLevel(const LevelLoadingInfo& levelInfo);


	private:
		static inline EventHandler <UnitsLoadEventArgs> UnitsLoadEventHan= EventHandler<UnitsLoadEventArgs>(UnitsLoadEvent);
		static inline EventHandler<WallsLoadEventArgs> WallsLoadEventHan = EventHandler<WallsLoadEventArgs>(WallsLoadEvent);
		static inline EventHandler<GraphicsLoadEventArgs> GraphicsLoadEventHan= EventHandler<GraphicsLoadEventArgs>(GraphicsLoadEvent);
	};
}