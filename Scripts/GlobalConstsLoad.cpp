
#include <EngineCore.h>
#include <string>
#include <string.h>
#include <fstream>
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
	if (!TryGetValue(GlobalConsts::DEF_GAMEOBJS_ONESIZE_SPRITERESOL, &line))
		throw exception("Missing value of sprites one resolution");
	LoadedGlobalConsts.GameObjs_OneSizeSpriteResolution = stof(line);

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

const string GlobalConstsLoad::CONSTS_PATH = "GlobalConsts.txt";
const char GlobalConstsLoad::CONFIG_DEF_END_SYM = ':';