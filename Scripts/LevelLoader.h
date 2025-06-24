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
		UnitsLoadEventArgs(forward_list<UnitObject*>* LoadedUnits)
			:LoadedUnits(LoadedUnits){

		}
		forward_list<UnitObject*>* LoadedUnits;
	};
	struct WallsLoadEventArgs {
		WallsLoadEventArgs(forward_list<WallObject*>* LoadedWalls) 
			:LoadedWalls(LoadedWalls){

		}
		forward_list<WallObject*>* LoadedWalls;
	};
	struct HeroesLoadEventArgs {
		HeroesLoadEventArgs(forward_list<HeroObject*>* LoadedHeroes)
			:LoadedHeroes(LoadedHeroes){

		}
		forward_list<HeroObject*>* LoadedHeroes;
	};
	struct GraphicsLoadEventArgs {
		GraphicsLoadEventArgs(forward_list<ICallbackRec_GraphRen*>* LoadedGraphics) 
			:LoadedGraphics(LoadedGraphics){

		}
		forward_list<ICallbackRec_GraphRen*>* LoadedGraphics;
	};

	class UnitsLoadEventAction :public IEventSubscriber<UnitsLoadEventArgs> {};
	class WallsLoadEventAction:public IEventSubscriber<WallsLoadEventArgs>{};
	class GraphicsLoadEventAction :public IEventSubscriber<GraphicsLoadEventArgs> {};
	class HeroesLoadEventAction: public IEventSubscriber<HeroesLoadEventArgs>{};


	class LevelLoader {
	public:
		static inline ExecutedEvent<HeroesLoadEventArgs> HeroesLoadEvent = ExecutedEvent<HeroesLoadEventArgs>();
		static inline ExecutedEvent<UnitsLoadEventArgs> UnitsLoadEvent = ExecutedEvent<UnitsLoadEventArgs>();
		static inline ExecutedEvent<WallsLoadEventArgs> WallsLoadEvent=ExecutedEvent<WallsLoadEventArgs>();
		static inline ExecutedEvent<GraphicsLoadEventArgs> GraphicsLoadEvent = ExecutedEvent<GraphicsLoadEventArgs>();

		static inline forward_list<HeroObject*> LoadedHeroes = forward_list<HeroObject*>();
		static inline forward_list<UnitObject*> LoadedUnits= forward_list<UnitObject*>();
		static inline forward_list <WallObject*> LoadedWalls = forward_list<WallObject*>();
		static inline forward_list <ICallbackRec_GraphRen*> LoadedGraphics= forward_list<ICallbackRec_GraphRen*>();

		static void LoadLevel(const LevelLoadingInfo& levelInfo);

		static UnitObjectCtorParams& GetUnitParams(const UnitLoadInfo& info, Texture* texBuffer);
		static UnitObject& LoadUnit(const UnitLoadInfo& info,Texture* texBuffer);
		static HeroObject& LoadHero(const HeroLoadInfo& info,Texture* texBuffer);
		static WallObject& LoadWall(const WallLoadInfo& info,Texture* texBuffer);

	private:
		static inline EventHandler <HeroesLoadEventArgs> HeroesLoadEventHan = EventHandler<HeroesLoadEventArgs>(HeroesLoadEvent);
		static inline EventHandler <UnitsLoadEventArgs> UnitsLoadEventHan= EventHandler<UnitsLoadEventArgs>(UnitsLoadEvent);
		static inline EventHandler<WallsLoadEventArgs> WallsLoadEventHan = EventHandler<WallsLoadEventArgs>(WallsLoadEvent);
		static inline EventHandler<GraphicsLoadEventArgs> GraphicsLoadEventHan= EventHandler<GraphicsLoadEventArgs>(GraphicsLoadEvent);
	};
}