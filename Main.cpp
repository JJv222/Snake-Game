#include "Naglowek.h"


int main()
{
    Menu MainMenu(sf::Vector2f(450, 500));

    if (MainMenu.Display()) {
        SnakeGame Game(sf::Vector2f(883, 628)); //834, 590 -with border / 768, 512- without border
        Game.Display();
    }
    return 0;
}
