#pragma once

#include <map>
#include <SFML/System.hpp>
#include <rapidxml.hpp>
#include <string>
#include <FStreamExts.h>
#include <CollectionsExts.h>

using namespace sf;
using namespace std;
using namespace rapidxml;

using namespace KrostganEngine;

#define _ObjSubsPairType		pair<std::byte,TObjInfoType*>
#define _ObjSubsCollection		vector<_ObjSubsPairType>

#define EMPTY_CATALOG_ID		(size_t)0
#define ABSENT_SUB_CATALOG_ID	(std::byte)0

namespace KrostganEngine::Core {
	template <typename TObjInfoType>
	class ObjectsCatalog{

	private:
		struct GetSubInfoFunc : public CollectionsExts::Predicate<const _ObjSubsPairType&> {

			GetSubInfoFunc(std::byte ID)
				:ID(ID) {}

			bool Condition(const _ObjSubsPairType& input) const override {
				return input.first == ID;
			}

			const std::byte ID;
		};

	private:
		static inline map<size_t, TObjInfoType*>		Catalog;
		static inline map<size_t, _ObjSubsCollection >	SubCatalog;

	public:

		static void					Add(TObjInfoType& obj) {
			if (obj.CatalogID == EMPTY_CATALOG_ID)
				return;

			if (Catalog.find(obj.CatalogID) == Catalog.end()) {
				Catalog.insert(pair<size_t, TObjInfoType*>(obj.CatalogID, &obj));
			}
		}
		static void					Remove(TObjInfoType& obj) {
			Remove(obj.CatalogID);
		}
		static void					Remove(size_t id) {
			Catalog.erase(id);
			auto subs = SubCatalog.find(id);
			if (subs != SubCatalog.end()) {
				for (auto& pr : (*subs).second) {
					delete pr.second;
				}
			}
			SubCatalog.erase(subs);
		}
		static size_t				GetCatalogSize() {
			return Catalog.size();
		}
		static TObjInfoType& GetObjectInfo(size_t id) {
			return *Catalog[id];
		}
		static TObjInfoType& GetObjectInfo(size_t id, std::byte subID) {

			if (subID == ABSENT_SUB_CATALOG_ID)
				return GetObjectInfo(id);
			else
				return *GetSubObjInfo(id, subID);
		}

		static void						AddSub(TObjInfoType& subObjInfo, std::byte subID) {

			size_t objID = subObjInfo.CatalogID;

			if (Catalog.find(objID) != Catalog.end()) {

				auto subs = SubCatalog.find(objID);
				if (subs == SubCatalog.end()) {

					auto nSub = pair<size_t, _ObjSubsCollection >
						(objID, _ObjSubsCollection());
					SubCatalog.insert(nSub);
					subs = SubCatalog.find(objID);
				}
				else {
					auto el = CollectionsExts::template Get<_ObjSubsCollection, _ObjSubsPairType>
						((*subs).second, GetSubInfoFunc(subID));
					if (el != nullptr)
						throw exception("Sub info is already defined.");
				}
				(*subs).second.push_back(_ObjSubsPairType(subID, &subObjInfo));
			}
		}
		static void						RemoveSub(size_t objID, std::byte subID) {
			auto sub = SubCatalog.find(objID);
			if (sub != SubCatalog.end()) {

				auto index = CollectionsExts::template IndexOf<_ObjSubsCollection, _ObjSubsPairType>
					((*sub).second, GetSubInfoFunc(subID));
				auto it = (*sub).second.begin();
				it += index;
				(*sub).second.erase(it);
			}
		}
		/// <summary>
		/// Return nullptr if catalog doesn't contain input subID
		/// </summary>
		/// <param name="id"></param>
		/// <param name="subID"></param>
		/// <returns></returns>
		static TObjInfoType* GetSubObjInfo(size_t id, std::byte subID) {

			if (subID == ABSENT_SUB_CATALOG_ID)
				return nullptr;

			auto subs = SubCatalog.find(id);
			if (subs != SubCatalog.end()) {

				return CollectionsExts::template Get<_ObjSubsCollection, _ObjSubsPairType>
					((*subs).second, GetSubInfoFunc(subID))->second;

			}
			return nullptr;
		}

		static void Unload() {
			for (auto& pair : Catalog) {
				delete pair.second;
			}
			Catalog.clear();

			for (auto& pair : SubCatalog) {
				for (auto& subsPair : pair.second) {
					delete subsPair.second;
				}
			}
			SubCatalog.clear();
		}

	protected:
		ObjectsCatalog() {}

	};

	struct ObjectLoadInfo {

		virtual ~ObjectLoadInfo(){}

		size_t CatalogID = EMPTY_CATALOG_ID;
		std::byte SubCatalogID = ABSENT_SUB_CATALOG_ID;

	protected:
		ObjectLoadInfo(){}
		ObjectLoadInfo(const ObjectLoadInfo& copy)
			:CatalogID(copy.CatalogID),
			SubCatalogID(copy.SubCatalogID){}
	};

	class ObjectsCatalogDeserial {

	public:
		static const pair<const string, const string>* ParseParamLine(const string& line) {

			size_t index = line.find(PAR_DEF_NAME_END_SYM);
			if (index == string::npos)
				return nullptr;
			string p1 = line.substr(0, index);
			string p2 = line.substr(index + 1, line.size() - index);
			FStreamExts::ClearPath(p1);
			FStreamExts::ClearPath(p2);
			return new pair<const string, const string>(p1, p2);
		}

		static inline const string PAR_DEF_NAME_END_SYM = ":";

	protected:
		ObjectsCatalogDeserial(){}
	};
}