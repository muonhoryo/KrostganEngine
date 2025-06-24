
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
	LoadedGlobalResources = new ExternalGlobalResources();
	Texture* texs[4]{};

	LoadedGlobalResources->UnitsSelectionAreaSprite = LoadTextureByDefinition(ExternalGlobalResources::DEF_UNITS_SELECTIONAREA_SPRITE_PATH, *buffer);
	LoadedGlobalResources->HeroesSelectionAreaSprite = LoadTextureByDefinition(ExternalGlobalResources::DEF_HEROES_SELECTIONAREA_SPRITE_PATH, *buffer);
	LoadedGlobalResources->CursorSprite_Attack= LoadTextureByDefinition(ExternalGlobalResources::DEF_CURSOR_ATTACK_SPRITE_PATH, *buffer);
	LoadedGlobalResources->UnitDeathEffectSprite= LoadTextureByDefinition(ExternalGlobalResources::DEF_UNIT_DEATHEFFECT_SPRITE_PATH, *buffer);
	LoadedGlobalResources->DefaultFont = LoadFontByDefinition(ExternalGlobalResources::DEF_DEFAULT_FONT_PATH, *buffer);

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
Font* ExtGlobalResourcesLoad::LoadFontByDefinition(const string& definition, string& buffer) {
	GetValueByDefinition(definition, buffer);
	FStreamExts::ClearPath(&buffer);
	Font* font = new Font();
	font->loadFromFile(buffer);
	return font;
}

const string ExtGlobalResourcesLoad::GLOBAL_RESOURCES_PATH = "GlobalResources.txt";
const char ExtGlobalResourcesLoad::RESOURCE_DEF_END_SYM = ':';