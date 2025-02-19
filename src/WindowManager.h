#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include <SFML/Graphics.hpp>

class WindowManager
{
public:
    sf::RenderWindow currentWindow;
    bool threadActive;
    bool threadDone;

    WindowManager(sf::RenderWindow window)
        : currentWindow(window), threadActive(false), threadDone(false)
    {
        // You can initialize other members or perform any setup here
    }
    void Start();
    void Stop();
};

#endif // WINDOW_MANAGER_H
