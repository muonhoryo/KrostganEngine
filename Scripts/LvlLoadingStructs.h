#pragma once

#include <string>
#include <vector>
#include <WorldTransfObj.h>
#include <rapidxml.hpp>

#define Attr		const pair<const string,const string>
#define AttrsCollectn		vector<Attr*>

using namespace std;
using namespace rapidxml;
using namespace KrostganEngine::GameObjects;

namespace KrostganEngine::Core {

	//
	//
	// Catalog info
	//
	//

	struct LvlObjAdditParams final {

		LvlObjAdditParams(const AttrsCollectn& Attrs)
			:Attrs(Attrs)
		{}
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
		std::byte				CatalogSubID;
		LvlObjAdditParams* AdditParams = nullptr;

		void Deserialize(const string& serInfo);
		void Deserialize(const xml_node<>& serInfo);

		WorldTransfObj* InstantiateObj() const;

		static vector<LvlObjInstantiationInfo*>* DeserializeRow(const string& row);
		static vector<LvlObjInstantiationInfo*>* DeserializeRow(const xml_node<>& rootNode);

		static inline const string LVLSER_ELEM_PARAMS_DEF = "&";
		static inline const string LVLSER_SUBINFO_SEPARATOR = ":";
		static inline const string LVLSER_ELEM_ROW_SEPARATOR = ";;";
	};
}