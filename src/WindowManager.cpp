#include "WindowManager.hpp"
#include "Utilities.hpp"
#include <iostream>

WindowManager::WindowManager(sf::RenderWindow &window) : currentWindow(window)
{
    direction = generateRandomDirectionVector();
    windowSize = currentWindow.getSize();
}

void WindowManager::update(sf::Vector2i &mousePosition)
{
    sf::Vector2i windowPosition = currentWindow.getPosition();

    if (isMouseInWindow(windowPosition, windowSize, mousePosition))
    {
        currentWindow.clear(sf::Color::Red);

        if (!collidedWithCursorLastUpdate)
        {
            collidedWithCursorLastUpdate = true;
            cursorCollisionCount += 1;
        }
    }
    else
    {
        collidedWithCursorLastUpdate = false;
        currentWindow.clear(sf::Color::Green);
    }

    // Reflect direction if near monitor edge
    if (isPointNearMonitorEdge(windowPosition, windowSize))
    {
        currentWindow.clear(sf::Color::Yellow);
        direction = reflectDirection(windowPosition, windowSize, direction);
    }

    // Move the window in the current direction
    int moveDistance = 5 * level;
    int offsetX = static_cast<int>(direction.x * moveDistance);
    int offsetY = static_cast<int>(direction.y * moveDistance);

    currentWindow.setPosition(sf::Vector2i(windowPosition.x + offsetX, windowPosition.y + offsetY));
    currentWindow.display();
}

void WindowManager::close()
{
    currentWindow.close();
}

bool WindowManager::isMouseInWindow(sf::Vector2i &windowPosition, sf::Vector2u &windowSize, sf::Vector2i &mousePosition)
{
    int xBegin = windowPosition.x;
    int xEnd = windowPosition.x + windowSize.x;
    int yBegin = windowPosition.y;
    int yEnd = windowPosition.y + windowSize.y;

    return (xBegin <= mousePosition.x && mousePosition.x <= xEnd) && (yBegin <= mousePosition.y && mousePosition.y <= yEnd);
}
