#pragma once

#include <map>
#include <SFML/System.hpp>
#include <rapidxml.hpp>

using namespace sf;
using namespace std;
using namespace rapidxml;

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
					auto el = CollectionsExts::Get<_ObjSubsCollection, _ObjSubsPairType>
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

				auto index = CollectionsExts::IndexOf<_ObjSubsCollection, _ObjSubsPairType>
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

				return CollectionsExts::Get<_ObjSubsCollection, _ObjSubsPairType>
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

	private:
		static inline map<size_t, TObjInfoType*>		Catalog;
		static inline map<size_t, _ObjSubsCollection >	SubCatalog;
	};
}