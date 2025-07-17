#pragma once

#include <SFML/System.hpp>
#include <LevelBypassMap.h>
#include <list>
#include <forward_list>
#include <vector>
#include <Extensions.h>

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

						index = CollectionsExts::IndexOf(endPnts_raw, vert);
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
					if (next_par->IsOut)
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

	public:

		//static list<Vector2f>* GetPath(Vector2f start, Vector2f end) {

		//	forward_list<BypassVertex*> donePnts;
		//	vector<BypassVertex*> endVerts = LevelBypassMapManager::GetBypassVertsToPnt(end);
		//	Path* result = nullptr;
		//	list<Path*> pathes;
		//	{
		//		vector<BypassVertex*> startVerts = LevelBypassMapManager::GetBypassVertsToPnt(start);
		//		Path* path=nullptr;
		//		for (auto& vert : startVerts) {
		//			path = new Path();
		//			path->Way.push_back(vert);
		//			path->Cost = Length(vert->GetPosition() - start);
		//			pathes.push_back(path);
		//		}
		//	}
		//	typename list<Path*>::iterator curr;
		//	typename list<Path*>::iterator it;
		//	typename list<Path*>::iterator itEnd;
		//	bool pickedHanPnt = false;
		//	typename list<Path*>::iterator changedPathIt;
		//	BypassVertex* head = nullptr;
		//	BypassVertex* handlePnt = nullptr;
		//	Path* newPath = nullptr;
		//	while (pathes.size() != 0) {
		//		//find min
		//		it = pathes.begin();
		//		itEnd = pathes.end();
		//		curr = it;
		//		++it;
		//		for (;it != itEnd;++it) {
		//			if ((*it)->Cost < (*curr)->Cost)
		//				curr = it;
		//		}
		//		if (result != nullptr && (*curr)->Cost > result->Cost)
		//			break;
		//		//handle ways
		//		head = (*curr)->Way.back();
		//		if (CollectionsExts::Contains(endVerts, head)) {

		//			//Path reached end

		//			(*curr)->Cost += Length(head->GetPosition() - end);

		//			if (result != nullptr) {
		//				if (result->Cost < (*curr)->Cost) {
		//					delete result;
		//					result = (*curr);
		//				}
		//				else {
		//					delete* curr;
		//				}
		//			}
		//			else {
		//				result = (*curr);
		//			}

		//			pathes.erase(curr);
		//			continue;
		//		}

		//		vector<BypassWay*> ways = vector<BypassWay*>(head->GetWays());
		//		sort(ways.begin(),ways.end(), WaysSorting());

		//		for (BypassWay* currWay : ways) {
		//			if (&currWay->First == head)
		//				handlePnt = &currWay->Second;
		//			else
		//				handlePnt = &currWay->First;

		//			if (CollectionsExts::Contains(donePnts, handlePnt))
		//				continue;



		//			//Check is there the handled point in any pathes
		//			pickedHanPnt = false;
		//			changedPathIt = pathes.begin();
		//			for (;changedPathIt != itEnd;++changedPathIt) {
		//				if ((*changedPathIt)->Way.back() == handlePnt) {
		//					pickedHanPnt = true;
		//					break;
		//				}
		//			}

		//			if (pickedHanPnt) {

		//				if ((*changedPathIt)->Cost > (*curr)->Cost + currWay->Cost) {
		//					delete* changedPathIt;
		//					pathes.erase(changedPathIt);
		//				}
		//				else
		//					continue;
		//			}
		//			newPath = new Path(**curr);
		//			newPath->Way.push_back(handlePnt);
		//			newPath->Cost += currWay->Cost;
		//			pathes.push_back(newPath);
		//		}
		//		donePnts.push_front(head);
		//		delete* curr;
		//		pathes.erase(curr);
		//	}
		//	if (result != nullptr)
		//	{
		//		list<Vector2f>& lst = *new list<Vector2f>();
		//		for (auto& el : result->Way)
		//			lst.push_back(el->GetPosition());
		//		lst.push_back(end);
		//		return &lst;
		//	}
		//	else
		//		return nullptr;
		//}

	private:
		PathFinding_Diijkstra(){}
	};
}