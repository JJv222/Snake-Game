#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <thread>

class Menu
{
private:
    sf::RenderWindow* window;

    sf::Text MainText;
    sf::Text ButtonPlay;
    sf::Font Mainfont;


public:
    Menu(sf::Vector2f);
    ~Menu();
    bool Display();
};
