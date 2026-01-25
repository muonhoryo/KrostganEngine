#pragma once

#include <LevelWorldObjsLoadInfo.h>
#include <SFML/System.hpp>
#include <ObjectsCatalog.h>

using namespace sf;
using namespace std;
using namespace rapidxml;

namespace KrostganEngine::Core {
	class WorldTransfObjsCatalog final : public ObjectsCatalog<WorldObjectLoadInfo> {

	private:
		WorldTransfObjsCatalog () :ObjectsCatalog<WorldObjectLoadInfo>(){}

	};

	class WorldTransfObjsCatalogDeserial {

	public:
		/// <summary>
		/// Fill objects catalog with objects, deserialized from xml-file
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
		static void										DeserializeCatalog(const string& serPath);
		/// <summary>
		/// Divide line of param definition and return pair with serialized name and value of param
		/// </summary>
		static const pair<const string, const string>* ParseParamLine(const string& line);
		/// <summary>
		/// Deserialize object's info only and return it
		/// </summary>
		static WorldObjectLoadInfo& DeserializeObjInfo(xml_node<>& serObj);

		static inline const string PAR_DEF_NAME_END_SYM = ":";

	private:
		/// <summary>
		/// Deserialize object info with its sub infos and add them to the ObjectsCatalog
		/// </summary>
		static void	DeserObjForCatalog(xml_node<>& serObj);

		static pair<std::byte, WorldObjectLoadInfo*>& ParseObjSubInfo(const WorldObjectLoadInfo& base, const xml_node<>& serObj);
		static pair<size_t, pair<std::byte, WorldObjectLoadInfo*>>& ParseObjSubinfo(const WorldObjectLoadInfo& base, const vector<string>& params);


	private:
		WorldTransfObjsCatalogDeserial() {}

	};
}