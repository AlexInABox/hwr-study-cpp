#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <SFML/Graphics.hpp>


/**
 * @brief Generates a random position somewhere inside the screen bounds with a given padding. The padding only applies to the right and bottom.
 *
 * @param padding The space between the random postion and the screen borders.
 * @return Random position as a sf::Vector2i.
 */
sf::Vector2i generateRandomPositionOnScreenWithPadding(int padding = 500);

/**
 * @brief Generates a random position around a given point within a fixed radius.
 *
 * @param point The center point.
 * @param radiusInPixels The radius within which to generate the position.
 * @return Random position as a sf::Vector2i.
 */
sf::Vector2i generateRandomPositionAroundPoint(const sf::Vector2i &point, int radiusInPixels);

/**
 * @brief Generates a random position within the bound of the screen
 * @param paddingToRight The padding to the right of the screen
 * @param paddingToBottom The padding to the bottom of the screen
 *
 * @return Random position as an sf::Vector2i
 */
sf::Vector2i generateRandomPositionWithPadding(int paddingToRight, int paddingToBottom);

/**
 * @brief Generates evenly spaced positions around a point in a circle.
 *
 * @param point The center point.
 * @param radiusInPixels The circle's radius.
 * @param index The index of the position.
 * @param maxIndex The total number of positions.
 * @return A spaced position as a sf::Vector2i.
 */
sf::Vector2i generateSpacedPositionsAroundPoint(const sf::Vector2i &point, int radiusInPixels, int index, int maxIndex);

/**
 * @brief Generates a random unit direction vector.
 *
 * @return A random normalized sf::Vector2f direction.
 */
sf::Vector2f generateRandomDirectionVector();

/**
 * @brief Checks if a point is near the edge of the monitor.
 *
 * @param point The point to check.
 * @param windowSize The size of the window.
 * @return True if near the edge, otherwise false.
 */
bool isPointNearMonitorEdge(const sf::Vector2i &point, const sf::Vector2u &windowSize);

/**
 * @brief Normalizes a vector.
 *
 * @param v The vector to normalize.
 * @return A normalized vector (unit length).
 */
sf::Vector2f normalize(const sf::Vector2f &v);

/**
 * @brief Reflects a movement direction when hitting screen edges.
 *
 * @param position The object's position.
 * @param windowSize The window's size.
 * @param direction The current movement direction.
 * @return The reflected movement direction.
 */
sf::Vector2f reflectDirection(const sf::Vector2i &position, const sf::Vector2u &windowSize, sf::Vector2f direction);

/**
 * @brief Saves the highscore to a file.
 *
 * @param highscore The highscore to save.
 */
void saveHighscore(int highscore);

/**
 * @brief Loads the highscore from a file.
 *
 * @return The loaded highscore. Returns 0 if no file exists.
 */
int loadHighscore();

/**
 * @brief Returns the reference to a random popup image texture.
 *
 * @return A random popup image texture.
 */
sf::Texture getRandomPopUpTexture();

#endif // UTILITIES_HPP