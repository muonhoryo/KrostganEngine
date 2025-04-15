

#include <EngineCore.h>

using namespace KrostganEngine::Core;

void GameMode::ExecuteCycle() {

    RenderWindow& wind = Engine::GetRenderWindow();

    while (wind.isOpen())
    {
        sf::Event event;
        while (wind.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                wind.close();
        }

        wind.clear();
        wind.display();
    }
}
void MainMenuMode::ExecuteCycle() {

}