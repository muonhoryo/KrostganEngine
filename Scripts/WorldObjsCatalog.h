#pragma once

#include <WorldObjectLoadInfo.h>
#include <SFML/System.hpp>
#include <ObjectsCatalog.h>

using namespace sf;
using namespace std;
using namespace rapidxml;

namespace KrostganEngine::Core {
	class WorldObjsCatalog final : public ObjectsCatalog<WorldObjectLoadInfo> {

	private:
		WorldObjsCatalog () :ObjectsCatalog<WorldObjectLoadInfo>(){}

	};

	class WorldObjsCatalogDeserial : public ObjectsCatalogDeserial {

	public:
		/// <summary>
		/// Fill objects catalog with objects, deserialized from xml-file
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
		static void					DeserializeCatalog(const string& serPath);
		/// <summary>
		/// Deserialize object's info only and return it
		/// </summary>
		static WorldObjectLoadInfo& DeserializeObjInfo(xml_node<>& serObj);

	private:
		/// <summary>
		/// Deserialize object info with its sub infos and add them to the ObjectsCatalog
		/// </summary>
		static void	DeserEffForCatalog(xml_node<>& serObj);

		static pair<std::byte, WorldObjectLoadInfo*>& ParseObjSubInfo(const WorldObjectLoadInfo& base, const xml_node<>& serObj);
		//static pair<size_t, pair<std::byte, WorldObjectLoadInfo*>>& ParseObjSubinfo(const WorldObjectLoadInfo& base, const vector<string>& params);


	private:
		WorldObjsCatalogDeserial() {}

	};
}