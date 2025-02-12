#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "GameManager.h"
#include "Utilities.h"

bool isMouseInWindow(sf::Vector2i& windowPosition, sf::Vector2u& windowSize, sf::Vector2i& mousePosition)
{
    int xBegin = windowPosition.x;
    int xEnd = windowPosition.x + windowSize.x;
    int yBegin = windowPosition.y;
    int yEnd = windowPosition.y + windowSize.y;

    return (xBegin <= mousePosition.x && mousePosition.x <= xEnd) && (yBegin <= mousePosition.y && mousePosition.y <= yEnd);
}

bool GameManager::threadActive = false;
bool GameManager::threadDone = true;
std::vector<sf::RenderWindow> active_windows;
std::vector<sf::Vector2f> directions_per_window;

void StartGame() {  // This must match the declaration in the header file
    GameManager::threadActive = true;
    GameManager::threadDone = false;

    std::cout << "GameManager started!" << std::endl;

    //Set up some windows
    for (int i = 0; i < 30; i++){
        active_windows.push_back(sf::RenderWindow(sf::VideoMode({100u, 100u}), "", sf::Style::None));
        directions_per_window.push_back(generateRandomDirectionVector());
    }
    for (int i = 0; i < active_windows.size(); i++){
        active_windows[i].setPosition(UTILITIES_HPP::generateSpacedPositionsAroundPoint(sf::Mouse::getPosition(), 500, i, active_windows.size()));
        active_windows[i].setFramerateLimit(30);
    }

    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    while (GameManager::threadActive) {
        mousePosition = sf::Mouse::getPosition();

        for (int i = 0; i < active_windows.size(); i++){
            sf::RenderWindow& currentWindow = active_windows[i];

            sf::Vector2i windowPosition = currentWindow.getPosition();
            sf::Vector2u windowSize = currentWindow.getSize();
            
            
            if (isMouseInWindow(windowPosition, windowSize, mousePosition)){
                currentWindow.clear(sf::Color::Red);
            } else {
                currentWindow.clear(sf::Color::Green);
            }


            // If we touch the edge the direction should (reflect) change.
            if (isPointNearMonitorEdge(windowPosition, windowSize)) {
                directions_per_window[i] = reflectDirection(windowPosition, windowSize, directions_per_window[i]);
            }
            // Move the window by moveDistance into a random direction!
            sf::Vector2f& direction = directions_per_window[i];
            int moveDistance = 18;
            int offsetX = static_cast<int>(direction.x * moveDistance);
            int offsetY = static_cast<int>(direction.y * moveDistance);

            // Set the new position of the window
            currentWindow.setPosition(sf::Vector2i(windowPosition.x + offsetX, windowPosition.y + offsetY));


            currentWindow.display();
        }
    }

    //Cleanup
    for (int i = 0; i < active_windows.size(); i++){
        sf::RenderWindow& currentWindow = active_windows[i];
        currentWindow.close();
    }
    active_windows.clear();

    GameManager::threadDone = true;
}

void GameManager::Start(){
    GameManager::threadActive = true;
    StartGame();
}

void GameManager::Stop(){
    GameManager::threadActive = false;
}