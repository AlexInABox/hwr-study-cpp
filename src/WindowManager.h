#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include <iostream>

class WindowManager
{
public:
    WindowManager(sf::RenderWindow &window) : currentWindow(window)
    {
        direction = generateRandomDirectionVector();
        windowSize = currentWindow.getSize();
    }

    int cursorCollisionCount = 0;

    void update(sf::Vector2i &mousePosition)
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

        // If we touch the edge the direction should (reflect) change.
        if (isPointNearMonitorEdge(windowPosition, windowSize))
        {
            currentWindow.clear(sf::Color::Yellow);
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

    void close()
    {
        currentWindow.close();
    }

private:
    sf::RenderWindow &currentWindow;
    sf::Vector2f direction;
    sf::Vector2u windowSize;
    bool collidedWithCursorLastUpdate = false;

    bool isMouseInWindow(sf::Vector2i &windowPosition, sf::Vector2u &windowSize, sf::Vector2i &mousePosition)
    {
        int xBegin = windowPosition.x;
        int xEnd = windowPosition.x + windowSize.x;
        int yBegin = windowPosition.y;
        int yEnd = windowPosition.y + windowSize.y;

        return (xBegin <= mousePosition.x && mousePosition.x <= xEnd) && (yBegin <= mousePosition.y && mousePosition.y <= yEnd);
    }
};

#endif // WINDOW_MANAGER_H
