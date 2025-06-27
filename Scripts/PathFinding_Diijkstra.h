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
		struct Path {

			list<BypassVertex*> Way;
			float Cost=0;
		};

	public:
		static list<Vector2f>* GetPath(Vector2f start, Vector2f end) {

			forward_list<BypassVertex*> donePnts;
			vector<BypassVertex*> endVerts = LevelBypassMapManager::GetBypassVertsToPnt(end);
			Path* result = nullptr;
			list<Path*> pathes;
			{
				vector<BypassVertex*> startVerts = LevelBypassMapManager::GetBypassVertsToPnt(start);
				Path* path=nullptr;
				for (auto& vert : startVerts) {
					path = new Path();
					path->Way.push_back(vert);
					path->Cost = Length(vert->GetPosition() - start);
					pathes.push_back(path);
				}
			}
			typename list<Path*>::iterator curr;
			typename list<Path*>::iterator it;
			typename list<Path*>::iterator itEnd;
			bool pickedHanPnt = false;
			typename list<Path*>::iterator changedPathIt;
			BypassVertex* head = nullptr;
			BypassVertex* handlePnt = nullptr;
			Path* newPath = nullptr;
			while (pathes.size() != 0) {
				//find min
				it = pathes.begin();
				itEnd = pathes.end();
				curr = it;
				++it;
				for (;it != itEnd;++it) {
					if ((*it)->Cost < (*curr)->Cost)
						curr = it;
				}
				if (result != nullptr && (*curr)->Cost > result->Cost)
					break;
				//handle ways
				head = (*curr)->Way.back();
				if (CollectionsExts::Contains(endVerts, head)) {

					//Path reached end

					(*curr)->Cost += Length(head->GetPosition() - end);

					if (result != nullptr) {
						if (result->Cost < (*curr)->Cost) {
							delete result;
							result = (*curr);
						}
						else {
							delete* curr;
						}
					}
					else {
						result = (*curr);
					}

					pathes.erase(curr);
					continue;
				}

				vector<BypassWay*> ways = vector<BypassWay*>(head->GetWays());
				sort(ways.begin(),ways.end(), WaysSorting());

				for (BypassWay* currWay : ways) {
					if (&currWay->First == head)
						handlePnt = &currWay->Second;
					else
						handlePnt = &currWay->First;

					if (CollectionsExts::Contains(donePnts, handlePnt))
						continue;



					//Check is there the handled point in any pathes
					pickedHanPnt = false;
					changedPathIt = pathes.begin();
					for (;changedPathIt != itEnd;++changedPathIt) {
						if ((*changedPathIt)->Way.back() == handlePnt) {
							pickedHanPnt = true;
							break;
						}
					}

					if (pickedHanPnt) {

						if ((*changedPathIt)->Cost > (*curr)->Cost + currWay->Cost) {
							delete* changedPathIt;
							pathes.erase(changedPathIt);
						}
						else
							continue;
					}
					newPath = new Path(**curr);
					newPath->Way.push_back(handlePnt);
					newPath->Cost += currWay->Cost;
					pathes.push_back(newPath);
				}
				donePnts.push_front(head);
				delete* curr;
				pathes.erase(curr);
			}
			if (result != nullptr)
			{
				list<Vector2f>& lst = *new list<Vector2f>();
				for (auto& el : result->Way)
					lst.push_back(el->GetPosition());
				lst.push_back(end);
				return &lst;
			}
			else
				return nullptr;
		}

	private:
		PathFinding_Diijkstra(){}
	};
}