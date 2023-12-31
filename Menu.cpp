#include "Menu.h"

Menu::Menu(sf::Vector2f WindowSize) // Inicjalizujemy referencję do okna
{
    //window
    window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(WindowSize.x), static_cast<unsigned int>(WindowSize.y)), "Gra");

    //font and text
    Mainfont.loadFromFile("Textures/Lobster_1.3.otf");
    MainText.setFont(Mainfont);
    MainText.setString("Snake the game by JJ222");
    MainText.setFillColor(sf::Color::Blue);
    MainText.setCharacterSize(24);
    MainText.setPosition(100, 20);

    //button play
    ButtonPlay.setFont(Mainfont);
    ButtonPlay.setString("Play");
    ButtonPlay.setCharacterSize(24);
    ButtonPlay.setFillColor(sf::Color::Green);
    ButtonPlay.setPosition(210, 100);

    //button exit
    ButtonExit.setFont(Mainfont);
    ButtonExit.setString("Exit");
    ButtonExit.setCharacterSize(24);
    ButtonExit.setFillColor(sf::Color::Green);
    ButtonExit.setPosition(210, 170);

}

Menu::~Menu()
{
    delete window;
}

bool Menu::Display()
{
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window->close();
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (ButtonPlay.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))))
                {
                    window->close();
                    return true;
                }
                if (ButtonExit.getGlobalBounds().contains(sf::Vector2f(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y))))
                {
                    window->close();
                    return false;
                }
            }
        }

        window->clear();////

        window->draw(MainText);                    ///draw window here
        window->draw(ButtonPlay);
        window->draw(ButtonExit);


        window->display();///
    }
    return true;
}
