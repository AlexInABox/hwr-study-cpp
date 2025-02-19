#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <memory>
#include "WindowManager.h"
#include "Utilities.h"

WindowManager::WindowManager(sf::RenderWindow window) : currentWindow(window), threadActive(false), threadDone(false)
{
    // Initialize the currentWindow or any other necessary members
}

bool isMouseInWindow(sf::Vector2i &windowPosition, sf::Vector2u &windowSize, sf::Vector2i &mousePosition)
{
    int xBegin = windowPosition.x;
    int xEnd = windowPosition.x + windowSize.x;
    int yBegin = windowPosition.y;
    int yEnd = windowPosition.y + windowSize.y;

    return (xBegin <= mousePosition.x && mousePosition.x <= xEnd) && (yBegin <= mousePosition.y && mousePosition.y <= yEnd);
}

void MainLoop()
{ // This must match the declaration in the header file
    std::cout << "Window started!" << std::endl;

    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    sf::Vector2f direction = generateRandomDirectionVector();

    while (threadActive && currentWindow.isOpen())
    {
        mousePosition = sf::Mouse::getPosition();

        if (!currentWindow.isOpen())
            continue;

        sf::Vector2i windowPosition = currentWindow.getPosition();
        sf::Vector2u windowSize = currentWindow.getSize();

        if (isMouseInWindow(windowPosition, windowSize, mousePosition))
        {
            currentWindow.clear(sf::Color::Red);
        }
        else
        {
            currentWindow.clear(sf::Color::Green);
        }

        // If we touch the edge the direction should (reflect) change.
        if (isPointNearMonitorEdge(windowPosition, windowSize))
        {
            direction = reflectDirection(windowPosition, windowSize, direction);
        }

        // Move the window by moveDistance into a random direction!
        int moveDistance = 18;
        int offsetX = static_cast<int>(direction.x * moveDistance);
        int offsetY = static_cast<int>(direction.y * moveDistance);

        // Set the new position of the window
        currentWindow.setPosition(sf::Vector2i(windowPosition.x + offsetX, windowPosition.y + offsetY));

        currentWindow.display();
    }

    // Cleanup
    currentWindow.close();

    threadDone = true;
}

void WindowManager::Start()
{
    threadActive = true;
    MainLoop();
}

void WindowManager::Stop()
{
    threadActive = false;
}