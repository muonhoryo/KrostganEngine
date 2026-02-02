#pragma once

#include <SFML/System.hpp>
#include <LevelBypassMap.h>
#include <list>
#include <forward_list>
#include <vector>
#include <_Extensions.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine;

namespace KrostganEngine::Core {
	class PathFinding_Diijkstra {

	private:
		struct PathVertex {
			
			PathVertex(BypassVertex& OwnVrtx)
				:OwnVrtx(OwnVrtx),
				Cost(FLT_MAX){
			}

			BypassVertex& OwnVrtx;
			PathVertex* PrevVrtx = nullptr;
			float Cost;
			bool IsOut=false;
		};

		struct Path {

			list<BypassVertex*> Way;
			float Cost=0;
		};

	public:
		static list<Vector2f>* GetPath(Vector2f start, Vector2f end) {

			vector<PathVertex*> map;
			forward_list<PathVertex*> currPnts;
			vector<PathVertex*> endPnts;
			vector<float> endPntAddCosts;
			PathVertex* endPnt = nullptr;
			{
				vector<BypassVertex*> startPnts_raw = LevelBypassMapManager::GetBypassVertsToPnt(start);
				vector<BypassVertex*> endPnts_raw = LevelBypassMapManager::GetBypassVertsToPnt(end);
				endPnts = vector<PathVertex*>(endPnts_raw.size());
				endPntAddCosts = vector<float>(endPnts_raw.size());
				auto endIt = LevelBypassMapManager::GetMapEnd();
				auto startIt = LevelBypassMapManager::GetMapStart();
				map= vector<PathVertex*>((int)(endIt - startIt));
				BypassVertex* vert = nullptr;
				for (int i=0,index=0;startIt != endIt;++startIt) {

					vert = *startIt;
					map[i] = new PathVertex(*vert);
					if (CollectionsExts::Contains(startPnts_raw, vert)) {	//pnt is one of start points

						SortedInsert(currPnts,map[i]);
						map[i]->Cost = Length(map[i]->OwnVrtx.GetPosition() - start);
					}
					else {

						index = (int)CollectionsExts::IndexOf(endPnts_raw, vert);
						if (index != string::npos) {	//pnt is one of end points

							endPnts[index] = map[i];
							endPntAddCosts[index] = Length(map[i]->OwnVrtx.GetPosition() - end);
						}
					}
					++i;
				}
			}

			PathVertex* curr = nullptr;
			BypassVertex* next = nullptr;
			PathVertex* next_par = nullptr;
			float newWayCost = 0;
			bool isEndPntNext = false;
			size_t endPntIndex = string::npos;
			float oldWayCost = 0;
			while (!currPnts.empty()) {

				curr = currPnts.front();
				currPnts.pop_front();
				if (endPnt != nullptr && curr->Cost > endPnt->Cost)
					break;

				for (auto path : curr->OwnVrtx.GetWays()) {

					//Convert pnt to her wrapper
					if (&path->First == &curr->OwnVrtx) {
						next = &path->Second;
					}
					else {
						next = &path->First;
					}
					for (auto parPnt : map) {
						if (&parPnt->OwnVrtx == next) {

							next_par = parPnt;
							break;
						}
					}

					//Check way
					if (next_par==nullptr || next_par->IsOut)
						continue;
					endPntIndex = CollectionsExts::IndexOf(endPnts, next_par);
					isEndPntNext = endPntIndex != string::npos;
					newWayCost = curr->Cost + path->Cost;
					oldWayCost = isEndPntNext ? next_par->Cost - endPntAddCosts[endPntIndex] : next_par->Cost;

					if (newWayCost < oldWayCost) {

						next_par->Cost = isEndPntNext? newWayCost+ endPntAddCosts[endPntIndex]:newWayCost;
						next_par->PrevVrtx = curr;
						if (isEndPntNext) {

							if (next_par != endPnt) {

								if (endPnt == nullptr ||
									endPnt->Cost > next_par->Cost) {

									endPnt = next_par;
								}
							}
						}
						else {

							SortedInsert(currPnts, curr);
						}
					}
				}
				
				curr->IsOut = true;
			}
			if (endPnt!= nullptr)
			{
				list<Vector2f>& lst = *new list<Vector2f>();
				lst.push_front(end);
				lst.push_front(endPnt->OwnVrtx.GetPosition());
				next_par = endPnt->PrevVrtx;
				while (next_par != nullptr) {

					lst.push_front(next_par->OwnVrtx.GetPosition());
					next_par = next_par->PrevVrtx;
				}
				return &lst;
			}
			else
				return nullptr;
		}

	private:
		static void SortedInsert(forward_list<PathVertex*>& list, PathVertex* pnt) {

			typename forward_list<PathVertex*>::iterator srt_currIt=list.begin();
			typename forward_list<PathVertex*>::iterator srt_prevIt = list.before_begin();
			typename forward_list<PathVertex*>::const_iterator srt_endIt=list.cend();

			for (;srt_currIt != srt_endIt;)
			{
				if ((*srt_currIt)->Cost >= pnt->Cost) {
					break;
				}
				++srt_currIt;
				++srt_prevIt;
			}
			list.insert_after(srt_prevIt,pnt);
		}

	private:
		PathFinding_Diijkstra(){}
	};
}