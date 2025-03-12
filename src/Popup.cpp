#include "Popup.hpp"
#include "Utilities.hpp"
#include "Sounds.hpp"
#include <SFML/Audio.hpp>
#include <iostream>

Popup::Popup() {
    randomNumber = rand() % 100;
    const std::u32string randomTitle = popupTitles[rand() % popupTitles.size()];
    const sf::String sfTitle(randomTitle);

    randomTexture = UTILITIES_HPP::getRandomPopUpTexture();

    currentWindow = sf::RenderWindow(sf::VideoMode({400u, 250u}), sfTitle, sf::Style::Close);
    currentWindow.setPosition(UTILITIES_HPP::generateRandomPositionOnScreenWithPadding(400));

    sf::Sprite background = sf::Sprite(randomTexture);

    const sf::Vector2u windowSize = currentWindow.getSize();
    const sf::Vector2u textureSize = randomTexture.getSize();

    const sf::Vector2f scale(
        static_cast<float>(windowSize.x) / textureSize.x,
        static_cast<float>(windowSize.y) / textureSize.y);
    background.setScale(scale);

    currentWindow.draw(background);
    currentWindow.display();

    openSound.play();
}

void Popup::update() {
    if (currentWindow.isOpen()) {
        while (const std::optional event = currentWindow.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                dismissSound.play();
                currentWindow.close();
                isClosed = true;
            }
        }
    }
}

void Popup::unHide() {
    if (currentWindow.isOpen()) {
        currentWindow.setVisible(true);
    }
}

void Popup::forceClose() {
    currentWindow.close();
    isClosed = true;
}

void Popup::loudClose() {
    dismissSound.play();
    currentWindow.close();
    isClosed = true;
}
