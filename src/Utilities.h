#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

const static double M_PI = 3.14159265358979323846;

// Function to generate a random position around a point with a fixed radius :3
sf::Vector2i generateRandomPositionAroundPoint(const sf::Vector2i &point, int radiusInPixels)
{
    // Generate a random angle between 0 and 2 * pi !!
    double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;

    // Compute the offset using the random angle and fixed radius °.°
    int offsetX = static_cast<int>(radiusInPixels * cos(theta));
    int offsetY = static_cast<int>(radiusInPixels * sin(theta));

    return sf::Vector2i(point.x + offsetX, point.y + offsetY);
}

// Function to generate a random position around a point with a fixed radius
sf::Vector2i generateSpacedPositionsAroundPoint(const sf::Vector2i &point, int radiusInPixels, int index, int maxIndex)
{
    // Generate the indexed fraction of a whole
    double theta = static_cast<double>((2 * M_PI) * (static_cast<double>(index + 1) / static_cast<double>(maxIndex)));

    int offsetX = static_cast<int>(radiusInPixels * cos(theta));
    int offsetY = static_cast<int>(radiusInPixels * sin(theta));

    return sf::Vector2i(point.x + offsetX, point.y + offsetY);
}

// Function to generate a random direction vector (unit vector)
sf::Vector2f generateRandomDirectionVector()
{
    double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;

    float directionX = static_cast<float>(cos(theta));
    float directionY = static_cast<float>(sin(theta));

    return sf::Vector2f(directionX, directionY);
}

const sf::Vector2u screenSize = sf::VideoMode::getDesktopMode().size;
bool isPointNearMonitorEdge(const sf::Vector2i &point, const sf::Vector2u &windowSize)
{
    // Offset in case windows cannot fully reach the edges
    constexpr int offset = 50;

    if (point.x - offset <= 0 || point.y - offset <= 0)
        return true;

    if (point.x + windowSize.x + offset >= screenSize.x)
        return true;

    if (point.y + windowSize.y + offset >= screenSize.y)
        return true;

    return false;
}

sf::Vector2f normalize(const sf::Vector2f &v)
{
    float length = std::sqrt(v.x * v.x + v.y * v.y);
    return (length > 0) ? sf::Vector2f(v.x / length, v.y / length) : sf::Vector2f(1.f, 0.f);
}

sf::Vector2f reflectDirection(const sf::Vector2i &position, const sf::Vector2u &windowSize, sf::Vector2f direction)
{
    double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;

    if (position.x <= 0 || position.x + 50 + windowSize.x >= screenSize.x)
    {
        direction.x = -direction.x;
        direction.y += static_cast<float>(sin(theta));
    }
    if (position.y <= 0 || position.y + 50 + windowSize.y >= screenSize.y)
    {
        direction.y = -direction.y;
        direction.x += static_cast<float>(cos(theta));
    }

    return normalize(direction);
}

// Function to save data to a JSON file
void saveHighscore(const int highscore)
{
    std::ofstream file("saveData.txt");
    if (file.is_open())
    {
        file << highscore;
        file.close();
    }
}

// Function to load data from a JSON file
int loadHighscore()
{
    std::ifstream file("saveData.txt");
    int data;
    if (file.is_open())
    {
        file >> data;
        file.close();
    }
    return data;
}

#endif // UTILITIES_HPP
