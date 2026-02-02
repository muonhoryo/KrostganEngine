
#include <SFML/Graphics.hpp>
#include <_EngineCore.h>

using namespace KrostganEngine::Core;
using namespace sf;

void LevelDeserializationMode :: ExecuteCycle() {
    FractionsDeserializator::DeserializeFractions("TestLevel_Fractions.xml");
    GameEffectsCatalogDeserial::DeserializeCatalog("TestLevelCatalog_GameEffects.xml");
    AbilitiesCatalogDeserial::DeserializeCatalog("TestLevelCatalog_Abilities.xml");
    WorldObjsCatalogDeserial::DeserializeCatalog("TestLevelCatalog_WorldObjs.xml");
    auto& levInf = LevelSerialization::DeserializeLevel("TestLevel.txt");
    LevelLoader::LoadLevel(levInf);
    Engine::ReqToSetMode_Game();

}