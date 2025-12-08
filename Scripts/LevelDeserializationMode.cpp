
#include <SFML/Graphics.hpp>
#include <EngineCore.h>

using namespace KrostganEngine::Core;
using namespace sf;

void LevelDeserializationMode :: ExecuteCycle() {
    ObjsCatalogDeserial::DeserializeCatalog("TestLevelCatalog.txt");
    auto& levInf = LevelSerialization::DeserializeLevel("TestLevel.txt");
    LevelLoader::LoadLevel(levInf);
    Engine::ReqToSetMode_Game();

}