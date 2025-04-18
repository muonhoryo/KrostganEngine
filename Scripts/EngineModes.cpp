

#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <LevelLoading.h>

using namespace KrostganEngine::Core;
using namespace sf;

GameMode::GameMode() :EngineMode() {
    Window = &Engine::GetRenderWindow();

}

void GameMode::ExecuteCycle() {

    Event event;
    while ((*Window).pollEvent(event))
    {
        if (event.type == Event::Closed)
            (*Window).close();
    }

    (*Window).clear();
    (*Window).display();
}
void MainMenuMode::ExecuteCycle() {

}
void LevelDeserializationMode :: ExecuteCycle() {
    auto& levInf = LevelSerialization::DeserializeLevel("TestLevel.txt");
    LevelLoader::LoadLevel(levInf);
    Engine::GetRenderModule().Initialize(LevelLoader::LoadedGraphics);
    Engine::ReqToSetMode_Game();
}