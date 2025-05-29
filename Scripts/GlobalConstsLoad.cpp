
#include <EngineCore.h>
#include <string>
#include <iostream>
#include <vector>
#include <SFML/System.hpp>

using namespace std;
using namespace sf;
using namespace KrostganEngine::Core;

GlobalConstsLoad::GlobalConstsLoad() :ValuesListDeserializer(), LoadedGlobalConsts(*new GlobalConsts()) {
}

const GlobalConsts& GlobalConstsLoad::LoadGlobalConsts() {
	DeserializeValues();

	string line = string();
	LoadedGlobalConsts.GameObjs_OneSizeSpriteResolution = DeserializeValueByDefinition(GlobalConsts::DEF_GAMEOBJS_ONESIZE_SPRITERESOL, &line);
	LoadedGlobalConsts.HeroesSelectArea_OneSizeSpriteResol = DeserializeValueByDefinition(GlobalConsts::DEF_HEROES_SELECTAREA_ONESIZE_SPRITERESOL, &line);
	LoadedGlobalConsts.UnitsSelectArea_OneSizeSpriteResol = DeserializeValueByDefinition(GlobalConsts::DEF_UNITS_SELECTAREA_ONESIZE_SPRITERESOL, &line);
	LoadedGlobalConsts.EPS = DeserializeValueByDefinition(GlobalConsts::DEF_EPS, &line);
	LoadedGlobalConsts.Orders_CancelTime = DeserializeValueByDefinition(GlobalConsts::DEF_ORDERS_CANCELTIME, &line);

	StrValuesArr.clear();
	return LoadedGlobalConsts;
}
const GlobalConsts& GlobalConstsLoad::GetLoadedConsts() {
	return LoadedGlobalConsts;
}

const string GlobalConstsLoad::GetFilePath() {
	return CONSTS_PATH;
}
const char GlobalConstsLoad::GetValuesDefEndSym() {
	return CONFIG_DEF_END_SYM;
}

float GlobalConstsLoad::DeserializeValueByDefinition(const string& definition, string* buffer) {
	if (!TryGetValue(definition, buffer)) {
		string str = "Missing value of " + definition;
		throw exception(str.c_str());
	}
	return stof(*buffer);
}

const string GlobalConstsLoad::CONSTS_PATH = "GlobalConsts.txt";
const char GlobalConstsLoad::CONFIG_DEF_END_SYM = ':';