#include "WindowManager.hpp"
#include "Utilities.hpp"
#include <iostream>

WindowManager::WindowManager()
{
    currentWindow = sf::RenderWindow(sf::VideoMode({250u, 200u}), "Freakish PopUp", sf::Style::Close);
    currentWindow.setPosition(UTILITIES_HPP::generateRandomPositionAroundPoint(sf::Vector2i(2000, 2000), 500));
}

void WindowManager::update()
{
    if (currentWindow.isOpen())
    {
        while (const std::optional event = currentWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                currentWindow.close();
                isClosed = true;
            }
        }
    }
}

void WindowManager::unHide()
{
    if (currentWindow.isOpen())
    {
        currentWindow.setVisible(true);
    }
}

void WindowManager::forceClose()
{
    currentWindow.close();
    isClosed = true;
}