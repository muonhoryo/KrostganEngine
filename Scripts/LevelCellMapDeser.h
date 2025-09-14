#pragma once

#include <vector>
#include <string>

using namespace std;

namespace KrostganEngine::Core {
	class LevelCellMapDeser {
	public:

		struct CellInfo {
			CellInfo();
			size_t	CatalogID;
			byte	SubCatalogID;
			vector<const pair<const string,const string>*> AdditionalParams;
		};

	public:
		static vector<vector<CellInfo*>*>& Deserialize(vector<string>& serObstrMap, size_t* columnCount);
		static Vector2f GetCellGlobalPosition(Vector2u mapCellPos);

		static inline const string DEF_LEVEL_CELL_MAP = "CellMap";
		static inline const string LVL_CMAP_START = "{";
		static inline const string LVL_CMAP_END = "}";

	private:
		LevelCellMapDeser() {}

		static vector<CellInfo*>* DeserializeRow(const string& row, bool* foundEnd);
		static CellInfo* DeserializeCellInfo(const string& str);

		static inline const string LVL_CMAP_ELEM_SEPARATOR = ";;";
		static inline const string LVL_CMAP_ROW_SEPARATOR = "\n";
		static inline const string LVL_CMAP_ELEM_PARAMS_DEF = "&";
		static inline const string LVL_CMAP_SUBINFO_SEPARATOR = ":";
	};
}
