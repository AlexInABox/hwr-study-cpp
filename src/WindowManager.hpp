#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <SFML/Graphics.hpp>

/**
 * @brief Manages an SFML window, handling movement and collision detection.
 */
class WindowManager
{
public:
    /**
     * @brief Constructs the WindowManager with a reference to a render window.
     *
     * @param window The SFML render window to manage.
     */
    WindowManager(sf::RenderWindow &window);

    /// Number of times the cursor has collided with the window.
    int cursorCollisionCount = 0;

    /// The current difficulty level affecting movement speed.
    int level = 1;

    /**
     * @brief Updates the window position and handles collisions.
     *
     * @param mousePosition The current mouse cursor position.
     */
    void update(sf::Vector2i &mousePosition);

    /**
     * @brief Closes the SFML window.
     */
    void close();

private:
    sf::RenderWindow &currentWindow;           ///< Reference to the SFML render window.
    sf::Vector2f direction;                    ///< Current movement direction.
    sf::Vector2u windowSize;                   ///< Cached window size.
    bool collidedWithCursorLastUpdate = false; ///< Tracks if the cursor was in the window last update.

    /**
     * @brief Checks if the mouse is inside the window boundaries.
     *
     * @param windowPosition The window's current position on the screen.
     * @param windowSize The window's size.
     * @param mousePosition The mouse cursor position.
     * @return True if the mouse is inside the window, false otherwise.
     */
    bool isMouseInWindow(sf::Vector2i &windowPosition, sf::Vector2u &windowSize, sf::Vector2i &mousePosition);
};

#endif // WINDOW_MANAGER_HPP
