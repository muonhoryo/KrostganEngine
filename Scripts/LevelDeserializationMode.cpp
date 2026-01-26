
#include <SFML/Graphics.hpp>
#include <EngineCore.h>

using namespace KrostganEngine::Core;
using namespace sf;

void LevelDeserializationMode :: ExecuteCycle() {
    GameEffectsCatalogDeserial::DeserializeCatalog("TestLevelCatalog_GameEffects.xml");
    WorldObjsCatalogDeserial::DeserializeCatalog("TestLevelCatalog_WorldObjs.xml");
    auto& levInf = LevelSerialization::DeserializeLevel("TestLevel.txt");
    LevelLoader::LoadLevel(levInf);
    Engine::ReqToSetMode_Game();

}