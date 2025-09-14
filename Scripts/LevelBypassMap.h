#pragma once

#include <LevelCellMapDeser.h>
#include <BypassVertex.h>
#include <ObjectsCatalog.h>
#include <vector>
#include <PrimitiveVisualShapes.h>

using namespace std;
using namespace KrostganEngine::UI;

namespace KrostganEngine::Core {
	class LevelBypassMapManager {
	public:
		static void Unload() {
			for (auto way : BypassWays)
				delete way;
			BypassWays.clear();

			for (auto vrt : BypassMap)
				delete vrt;
			BypassMap.clear();
		}
		static void LoadFromLevelMap(const vector<vector<LevelCellMapDeser::CellInfo*>*>& map) {

			Unload();

			WallLoadInfo* wallinf = nullptr;
			vector<size_t> wallIndexes;
			forward_list<Vector2u> addedPnts;

			for (int i = 0;i < ObjectsCatalog::GetCatalogSize();++i) {			
				wallinf = dynamic_cast<WallLoadInfo*>(ObjectsCatalog::GetObjectInfo(i));
				if (wallinf != nullptr)
					wallIndexes.push_back(wallinf->CatID);
			}

			if (wallIndexes.size() ==0)
				return;

			Vector2u pnt;

			if (map[0]->size() > 1 && map[1]->size() > 1) {

				//first corner
				if (IsWall(wallIndexes, (*map[0])[0])) {

					if (!IsWall(wallIndexes, (*map[1])[1]) &&
						!IsWall(wallIndexes, (*map[0])[1]) &&
						!IsWall(wallIndexes, (*map[1])[0]))
					{
						pnt = Vector2u(1, 1);
						addedPnts.push_front(pnt);
						BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
					}
				}

				size_t index = map[0]->size() - 1;
				for (size_t i = 1;i < index;++i) {		//first row

					if (IsWall(wallIndexes, (*map[0])[i])) {

						//left
						if (!IsWall(wallIndexes, (*map[1])[i-1]) &&		//left bottom
							!IsWall(wallIndexes, (*map[0])[i-1]) &&		//left
							!IsWall(wallIndexes, (*map[1])[i]))			//bottom
						{
							pnt = Vector2u(1,(unsigned int)i-1);
							if (!Contains(pnt, addedPnts)) {

								addedPnts.push_front(pnt);
								BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
							}
						}
						//right
						if (!IsWall(wallIndexes, (*map[1])[i + 1]) &&		//right bottom
							!IsWall(wallIndexes, (*map[0])[i + 1]) &&		//right
							!IsWall(wallIndexes, (*map[1])[i]))			//bottom
						{
							pnt = Vector2u(1,(unsigned int)i + 1);
							if (!Contains(pnt, addedPnts)) {

								addedPnts.push_front(pnt);
								BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
							}
						}
					}
				}
				//last corner of first row
				if (IsWall(wallIndexes, (*map[0])[index])) {

					if (!IsWall(wallIndexes, (*map[1])[index-1]) &&
						!IsWall(wallIndexes, (*map[0])[index-1]) &&
						!IsWall(wallIndexes, (*map[1])[index]))
					{
						pnt = Vector2u(1,(unsigned int)index-1);
						if (!Contains(pnt, addedPnts)) {

							addedPnts.push_front(pnt);
							BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
						}
					}
				}
			}	 //first row

			size_t columnCount = map.size();

			for (size_t i = 1;i < columnCount - 1;++i){		//mid rows

				//first cell
				if (IsWall(wallIndexes, (*map[i])[0])) {

					//right top
					if (!IsWall(wallIndexes, (*map[i-1])[1]) &&		//right top
						!IsWall(wallIndexes, (*map[i-1])[0]) &&		//top
						!IsWall(wallIndexes, (*map[i])[1]))			//right
					{
						pnt = Vector2u((unsigned int)i-1,1);
						if (!Contains(pnt, addedPnts)) {

							addedPnts.push_front(pnt);
							BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
						}
					}
					//right bottom
					if (!IsWall(wallIndexes, (*map[i+1])[1]) &&		//right bottom
						!IsWall(wallIndexes, (*map[i])[1]) &&		//right
						!IsWall(wallIndexes, (*map[i+1])[0]))			//bottom
					{
						pnt = Vector2u((unsigned int)i+1,1);
						if (!Contains(pnt, addedPnts)) {

							addedPnts.push_front(pnt);
							BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
						}
					}
				}

				//true mid cells
				size_t rowSize = (*map[i]).size();
				for (size_t j = 1;j < rowSize - 1;++j) {
					if (IsWall(wallIndexes, (*map[i])[j])) {

						//right top
						if (!IsWall(wallIndexes, (*map[i - 1])[j+1]) &&		//right top
							!IsWall(wallIndexes, (*map[i - 1])[j]) &&		//top
							!IsWall(wallIndexes, (*map[i])[j+1]))			//right
						{
							pnt = Vector2u((unsigned int)i - 1, (unsigned int)j+1);
							if (!Contains(pnt, addedPnts)) {

								addedPnts.push_front(pnt);
								BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
							}
						}
						//right bottom
						if (!IsWall(wallIndexes, (*map[i + 1])[j+1]) &&		//right bottom
							!IsWall(wallIndexes, (*map[i])[j+1]) &&		//right
							!IsWall(wallIndexes, (*map[i + 1])[j]))			//bottom
						{
							pnt = Vector2u((unsigned int)i + 1, (unsigned int)j+1);
							if (!Contains(pnt, addedPnts)) {

								addedPnts.push_front(pnt);
								BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
							}
						}
						//left bottom
						if (!IsWall(wallIndexes, (*map[i + 1])[j - 1]) &&		//left bottom
							!IsWall(wallIndexes, (*map[i])[j - 1]) &&		//left
							!IsWall(wallIndexes, (*map[i + 1])[j]))			//bottom
						{
							pnt = Vector2u((unsigned int)i + 1, (unsigned int)j - 1);
							if (!Contains(pnt, addedPnts)) {

								addedPnts.push_front(pnt);
								BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
							}
						}
						//left top
						if (!IsWall(wallIndexes, (*map[i - 1])[j - 1]) &&		//left top
							!IsWall(wallIndexes, (*map[i])[j - 1]) &&		//left
							!IsWall(wallIndexes, (*map[i - 1])[j]))			//top
						{
							pnt = Vector2u((unsigned int)i - 1, (unsigned int)j - 1);
							if (!Contains(pnt, addedPnts)) {

								addedPnts.push_front(pnt);
								BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
							}
						}
					}
				}

				//last cell of row
				if (IsWall(wallIndexes, (*map[i])[rowSize - 1])) {

					//left bottom
					if (!IsWall(wallIndexes, (*map[i + 1])[rowSize - 2]) &&		//left bottom
						!IsWall(wallIndexes, (*map[i])[rowSize - 2]) &&		//left
						!IsWall(wallIndexes, (*map[i + 1])[rowSize-1]))			//bottom
					{
						pnt = Vector2u(i + 1, rowSize - 2);
						if (!Contains(pnt, addedPnts)) {

							addedPnts.push_front(pnt);
							BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
						}
					}
					//left top
					if (!IsWall(wallIndexes, (*map[i - 1])[rowSize-2]) &&		//left top
						!IsWall(wallIndexes, (*map[i])[rowSize-2]) &&		//left
						!IsWall(wallIndexes, (*map[i - 1])[rowSize-1]))			//top
					{
						pnt = Vector2u((unsigned int)i - 1, (unsigned int)rowSize-2);
						if (!Contains(pnt, addedPnts)) {

							addedPnts.push_front(pnt);
							BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
						}
					}
				}
			}

			//first cell of last row
			if (IsWall(wallIndexes, (*map[columnCount - 1])[0])) {

				//right top
				if (!IsWall(wallIndexes, (*map[columnCount - 2])[1]) &&		//right top
					!IsWall(wallIndexes, (*map[columnCount - 2])[0]) &&		//top
					!IsWall(wallIndexes, (*map[columnCount-1])[1]))			//right
				{
					pnt = Vector2u((unsigned int)columnCount - 2, 1);
					if (!Contains(pnt, addedPnts)) {

						addedPnts.push_front(pnt);
						BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
					}
				}
			}

			size_t rowSize = (*map[columnCount - 1]).size();

			//mid cells of last row
			for (size_t i = 1;i < rowSize-1;++i) {

				if (IsWall(wallIndexes, (*map[columnCount - 1])[i])) {

					//right top
					if (!IsWall(wallIndexes, (*map[columnCount - 2])[i + 1]) &&		//right top
						!IsWall(wallIndexes, (*map[columnCount - 2])[i]) &&		//top
						!IsWall(wallIndexes, (*map[columnCount - 1])[i + 1]))			//right
					{
						pnt = Vector2u((unsigned int)columnCount - 2, i + 1);
						if (!Contains(pnt, addedPnts)) {

							addedPnts.push_front(pnt);
							BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
						}
					}
					//left top
					if (!IsWall(wallIndexes, (*map[columnCount - 2])[i - 1]) &&		//left top
						!IsWall(wallIndexes, (*map[columnCount - 1])[i - 1]) &&		//left
						!IsWall(wallIndexes, (*map[columnCount - 2])[i]))			//top
					{
						pnt = Vector2u((unsigned int)columnCount - 2, (unsigned int)i - 1);
						if (!Contains(pnt, addedPnts)) {

							addedPnts.push_front(pnt);
							BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
						}
					}
				}
			}

			//last corner
			if (IsWall(wallIndexes, (*map[columnCount - 1])[rowSize-1])) {

				//left top
				if (!IsWall(wallIndexes, (*map[columnCount - 2])[rowSize - 2]) &&		//left top
					!IsWall(wallIndexes, (*map[columnCount - 1])[rowSize-2]) &&		//left
					!IsWall(wallIndexes, (*map[columnCount - 2])[rowSize-1]))			//top
				{
					pnt = Vector2u((unsigned int)columnCount - 2, (unsigned int)rowSize-2);
					if (!Contains(pnt, addedPnts)) {

						addedPnts.push_front(pnt);
						BypassMap.push_back(new BypassVertex(LevelCellMapDeser::GetCellGlobalPosition(pnt)));
					}
				}
			}

			GenerateBypassWays(map);
		}

		static typename vector<BypassVertex*>::iterator GetMapStart() {
			return BypassMap.begin();
		}
		static typename vector<BypassVertex*>::iterator GetMapEnd() {
			return BypassMap.end();
		}
		static vector<BypassVertex*> GetBypassVertsToPnt(Vector2f pnt) {

			vector<BypassVertex*> verts;
			Segment segm(pnt,Vector2f(0,0));
			for (auto& it : BypassMap) {
				segm.Second = it->GetPosition();
				if (!Engine::GetPhysicsEngine().RayHit(segm,
					(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings))) {
					verts.push_back(it);
				}
			}
			return verts;
		}

	private:
		static bool IsWall(const vector<size_t>& Indexes, LevelCellMapDeser::CellInfo* cell) {
			
			for (int i = 0;i < Indexes.size();++i)
				if (Indexes[i] == cell->CatalogID)
					return true;
			return false;
		}
		static bool Contains(Vector2u vertexPos, forward_list<Vector2u>& addedPnts) {

			for (auto& it : addedPnts) {
				if (vertexPos == it)
					return true;
			}
			return false;
		}
		static void GenerateBypassWays(const vector<vector<LevelCellMapDeser::CellInfo*>*>& map) {

			Segment segm(Vector2f(0,0),Vector2f(0,0));

			for (BypassVertex* vert : BypassMap) {

				segm.First = vert->GetPosition();
				for (BypassVertex* target : BypassMap) {

					if (target == vert)
						continue;

					if (vert->CheckWayTo(*target))
						continue;

					segm.Second = target->GetPosition();
					if (!Engine::GetPhysicsEngine().RayHit(segm,
						(PhysicsLayer)((int)PhysicsLayer::Decorations | (int)PhysicsLayer::Buildings))) {

						BypassWays.push_back(&vert->GenerateWay(*target));
					}
				}
			}
		}

		static inline vector<BypassVertex*> BypassMap;
		static inline vector<BypassWay*> BypassWays;
	};
}