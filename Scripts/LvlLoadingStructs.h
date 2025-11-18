#pragma once

#include <string>
#include <vector>
#include <WorldTransfObj.h>

#define Attr		const pair<const string,const string>
#define AttrsCollectn	vector<Attr*>

using namespace std;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {

	//
	//
	// Catalog info
	//
	//

	struct LvlObjAdditParams final {

		LvlObjAdditParams(const AttrsCollectn& Attrs)
			:Attrs(Attrs) {}
		~LvlObjAdditParams() {
			for (auto& attr : Attrs) {
				delete attr;
			}
		}

		AttrsCollectn Attrs;
	};

	struct LvlObjInstantiationInfo final {

		LvlObjInstantiationInfo();
		~LvlObjInstantiationInfo() {
			if (AdditParams != nullptr)
				delete AdditParams;
		}

		size_t				CatalogID;
		byte				CatalogSubID;
		LvlObjAdditParams* AdditParams = nullptr;

		void Deserialize(const string& serInfo);
		WorldTransfObj* InstantiateObj() const;

		static vector<LvlObjInstantiationInfo*>* DeserializeRow(const string& row);

		static inline const string LVLSER_ELEM_PARAMS_DEF = "&";
		static inline const string LVLSER_SUBINFO_SEPARATOR = ":";
		static inline const string LVLSER_ELEM_ROW_SEPARATOR = ";;";
	};
}