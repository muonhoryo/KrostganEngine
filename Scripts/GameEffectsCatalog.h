#pragma once

#include <SFML/System.hpp>
#include <ObjectsCatalog.h>
#include <ComposeGameEffectLoadInfo.h>

using namespace sf;
using namespace std;
using namespace rapidxml;

namespace KrostganEngine::Core {
	class GameEffectsCatalog final : public ObjectsCatalog<ComposeGameEffectLoadInfo> {

	private:
		GameEffectsCatalog() :ObjectsCatalog<ComposeGameEffectLoadInfo>() {}

	};

	class GameEffectsCatalogDeserial : public ObjectsCatalogDeserial {

	public:
		/// <summary>
		/// Fill objects catalog with objects, deserialized from xml-file
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
		static void							DeserializeCatalog(const string& serPath);
		/// <summary>
		/// Deserialize object's info only and return it
		/// </summary>
		static ComposeGameEffectLoadInfo& DeserializeObjInfo(xml_node<>& serObj);

	private:
		/// <summary>
		/// Deserialize object info with its sub infos and add them to the ObjectsCatalog
		/// </summary>
		static void	DeserEffForCatalog(xml_node<>& serObj);

		static pair<std::byte, ComposeGameEffectLoadInfo*>& ParseObjSubInfo(const ComposeGameEffectLoadInfo& base, const xml_node<>& serObj);
		//static pair<size_t, pair<std::byte, ComposeGameEffectLoadInfo*>>& ParseObjSubinfo(const ComposeGameEffectLoadInfo& base, const vector<string>& params);


	private:
		GameEffectsCatalogDeserial() {}

	};
}