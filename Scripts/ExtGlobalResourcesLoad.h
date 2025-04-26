#pragma once

#include <ExternalGlobalResources.h>
#include <ValuesListDeserializer.h>

namespace KrostganEngine::Core {
	class ExtGlobalResourcesLoad:ValuesListDeserializer {
	public:
		ExtGlobalResourcesLoad();
		~ExtGlobalResourcesLoad(){}

		const ExternalGlobalResources& LoadGlobalResources();
		const ExternalGlobalResources& GetLoadedResources();

	private:
		ExternalGlobalResources* LoadedGlobalResources;

		const string GetFilePath() override;
		const char GetValuesDefEndSym() override;

		void GetValueByDefinition(const string& definition, string& buffer);
		Texture* LoadTextureByDefinition(const string& definition,string& buffer);

		static const string GLOBAL_RESOURCES_PATH;
		static const char RESOURCE_DEF_END_SYM;
	};
}