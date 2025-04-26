
#include <ExtGlobalResourcesLoad.h>
#include <string>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <Extensions.h>

using namespace sf;
using namespace std;
using namespace KrostganEngine::Core;

ExtGlobalResourcesLoad::ExtGlobalResourcesLoad() :ValuesListDeserializer() { LoadedGlobalResources = nullptr; }

const ExternalGlobalResources& ExtGlobalResourcesLoad::LoadGlobalResources() {
	DeserializeValues();

	string* buffer = new string();
	Texture* texs[2]{};

	texs[0] = LoadTextureByDefinition(ExternalGlobalResources::DEF_UNITS_SELECTIONAREA_SPRITE_PATH, *buffer);
	texs[1] = LoadTextureByDefinition(ExternalGlobalResources::DEF_HEROES_SELECTIONAREA_SPRITE_PATH, *buffer);
	
	LoadedGlobalResources = new ExternalGlobalResources(*texs[0], *texs[1]);

	delete buffer;

	return *LoadedGlobalResources;
}
const ExternalGlobalResources& ExtGlobalResourcesLoad::GetLoadedResources() {
	if (LoadedGlobalResources == nullptr)
		return LoadGlobalResources();
	return *LoadedGlobalResources;
}

const string ExtGlobalResourcesLoad::GetFilePath() {
	return GLOBAL_RESOURCES_PATH;
}
const char ExtGlobalResourcesLoad::GetValuesDefEndSym() {
	return RESOURCE_DEF_END_SYM;
}

void ExtGlobalResourcesLoad::GetValueByDefinition(const string& definition, string& buffer) {
	if (!TryGetValue(definition, &buffer)) {
		string std = "Missing value of " + definition;
		throw exception(std.c_str());
	}
}
Texture* ExtGlobalResourcesLoad::LoadTextureByDefinition(const string& definition, string& buffer) {
	GetValueByDefinition(definition, buffer);
	FStreamExts::ClearPath(&buffer);
	Texture* tex = new Texture();
	tex->loadFromFile(buffer);
	return tex;
}

const string ExtGlobalResourcesLoad::GLOBAL_RESOURCES_PATH = "GlobalResources.txt";
const char ExtGlobalResourcesLoad::RESOURCE_DEF_END_SYM = ':';