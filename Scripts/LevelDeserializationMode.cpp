

#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <LevelLoading.h>

using namespace KrostganEngine::Core;
using namespace sf;

void LevelDeserializationMode :: ExecuteCycle() {
    auto& levInf = LevelSerialization::DeserializeLevel("TestLevel.txt");
    LevelLoader::LoadLevel(levInf);
    Engine::ReqToSetMode_Game();
}