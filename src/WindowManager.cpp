#include "WindowManager.hpp"
#include "Utilities.hpp"
#include <iostream>

WindowManager::WindowManager()
{
    randomNumber = rand() % 100;
    const std::u32string randomTitle = popupTitles[rand() % popupTitles.size()];
    const sf::String sfTitle(randomTitle);

    randomTexture = UTILITIES_HPP::getRandomPopUpTexture();

    currentWindow = sf::RenderWindow(sf::VideoMode({400u, 250u}), sfTitle, sf::Style::Close);
    currentWindow.setPosition(UTILITIES_HPP::generateRandomPositionAroundPoint(sf::Vector2i(2000, 2000), 500));

    sf::Sprite background = sf::Sprite(randomTexture);

    sf::Vector2u windowSize = currentWindow.getSize();
    sf::Vector2u textureSize = randomTexture.getSize();

    sf::Vector2f scale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y);
    background.setScale(scale);

    currentWindow.draw(background);
    currentWindow.display();
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