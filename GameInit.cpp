
#include <SFML/Graphics.hpp>
#include <EngineCore.h>
#include <iostream>
#include <optional>
using namespace std;
using namespace sf;

using namespace KrostganEngine::Core;

void GameInit::Initialize() {

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