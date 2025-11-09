#pragma once

#include <vector>
#include <string>
#include <LevelLoadingInfo.h>

using namespace std;

namespace KrostganEngine::Core {
	class LevelCellMapDeser {
	public:
		static vector<vector<LvlObjInstantiationInfo*>*>& Deserialize(vector<string>& serObstrMap, size_t* columnCount);
		static Vector2f GetCellGlobalPosition(Vector2u mapCellPos);

		static inline const string DEF_LEVEL_CELL_MAP = "CellMap";
		static inline const string LVL_CMAP_START = "{";
		static inline const string LVL_CMAP_END = "}";

	private:
		LevelCellMapDeser() {}

		static vector<LvlObjInstantiationInfo*>* DeserializeRow(const string& row, bool* foundEnd);

		static inline const string LVL_CMAP_ROW_SEPARATOR = "\n";
	};
}
