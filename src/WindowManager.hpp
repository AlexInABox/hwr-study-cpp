#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <SFML/Graphics.hpp>

/**
 * @brief A custom wrapper for a PopUp window in the game. Each instance of this class manages a single popup window.
 */
class WindowManager
{
public:
    /**
     * @brief Constructs a PopUp with random properties.
     */
    WindowManager();

    /// The current difficulty level affecting some randomness maybe?
    int level = 1;

    /// The state of the current window.
    bool isClosed = false;

    /**
     * @brief Draw a frame for the window.
     */
    void update();

    /**
     * @brief Call this every 2 seconds just incase the user minimized a popup instead of closing it.
     */
    void unHide();

    /**
     * @brief Meta function that should destroy the window incase the main application stops.
     */
    void forceClose();

private:
    sf::RenderWindow currentWindow; ///< Reference to the SFML render window.
};

#endif // WINDOW_MANAGER_HPP