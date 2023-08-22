#include "Naglowek.h"


int main()
{
    Menu MainMenu(sf::Vector2f(450, 500));

    if (MainMenu.Display()) {
        SnakeGame Game(sf::Vector2f(1200, 900));
        Game.Display();
    }
    return 0;
}
