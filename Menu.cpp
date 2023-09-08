#include "Menu.h"

Menu::Menu(sf::Vector2f WindowSize) // Inicjalizujemy referencjê do okna
{
    //window
    window = new sf::RenderWindow(sf::VideoMode(static_cast<unsigned int>(WindowSize.x), static_cast<unsigned int>(WindowSize.y)), "Gra");

    //font and text
    Mainfont.loadFromFile("Textures/arial.ttf");
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
                    std::cout << "witam";
                    window->close();
                    return true;
                }
            }
        }

        window->clear();////

        window->draw(MainText);                    ///draw window here
        window->draw(ButtonPlay);


        window->display();///
    }
    return true;
}
