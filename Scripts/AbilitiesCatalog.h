#pragma once

#include <ObjectsCatalog.h>
#include <AbilityLoadInfo.h>

using namespace KrostganEngine::Core;

namespace KrostganEngine::GameObjects {

	class AbilitiesCatalog final : public ObjectsCatalog<AbilityLoadInfo> {

	private:
		AbilitiesCatalog() :ObjectsCatalog<AbilityLoadInfo>() {}

	};

	class AbilitiesCatalogDeserial : public ObjectsCatalogDeserial {

	public:
		/// <summary>
		/// Fill objects catalog with objects, deserialized from xml-file
		/// </summary>
		/// <param name="line"></param>
		/// <returns></returns>
		static void				DeserializeCatalog(const string& serPath);
		/// <summary>
		/// Deserialize object's info only and return it
		/// </summary>
		static AbilityLoadInfo& DeserializeObjInfo(xml_node<>& serObj);

	private:
		/// <summary>
		/// Deserialize object info with its sub infos and add them to the ObjectsCatalog
		/// </summary>
		static void	DeserAbilityForCatalog(xml_node<>& serObj);

		static pair<std::byte, AbilityLoadInfo*>& ParseObjSubInfo(const AbilityLoadInfo& base, const xml_node<>& serObj);


	private:
		AbilitiesCatalogDeserial() {}

	};
}