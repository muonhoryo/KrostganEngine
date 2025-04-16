

#include <SFML/Graphics.hpp>
#include <EngineCore.h>

using namespace KrostganEngine::Core;
using namespace sf;

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
GameMode::GameMode():EngineMode() {
    Window = &Engine::GetRenderWindow();
}

void MainMenuMode::ExecuteCycle() {

}

void LevelDeserializationMode :: ExecuteCycle() {
    Engine::ReqToSetMode_Game();
}