#pragma once

#include <vector>
#include <string>

using namespace std;

namespace KrostganEngine::Core {
	class LevelCellMapDeser {
	public:
		struct CellInfo {
			size_t CatalogID;
			vector<string> AdditionalParams;
		};

	public:
		static vector<vector<CellInfo*>*>& Deserialize(vector<string>& serObstrMap, size_t* columnCount);
		static Vector2f GetCellGlobalPosition(Vector2u mapCellPos);

		static inline const string DEF_LEVEL_CELL_MAP = "CellMap";
		static inline const string LEVEL_CELL_MAP_START = "{";
		static inline const string LEVEL_CELL_MAP_END = "}";

		static inline const size_t EMPTY_CATALOG_ID = 0;

	private:
		LevelCellMapDeser() {}

		static vector<CellInfo*>* DeserializeRow(const string& row, bool* foundEnd);
		static CellInfo* DeserializeCellInfo(const string& str);

		static inline const string LEVEL_CELL_MAP_ELEM_SEPARATOR = ";;";
		static inline const string LEVEL_CELL_MAP_ROW_SEPARATOR = "\n";
		static inline const string LEVEL_CELL_MAP_ELEM_PARAMS_DEF = "&";
		static inline const string LEVEL_CELL_MAP_ELEM_PARAMS_NAME_END = ":";
	};
}
