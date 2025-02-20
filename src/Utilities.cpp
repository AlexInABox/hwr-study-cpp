#include "Utilities.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

const sf::Vector2u screenSize = sf::VideoMode::getDesktopMode().size;

sf::Vector2i generateRandomPositionAroundPoint(const sf::Vector2i &point, int radiusInPixels)
{
    double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
    int offsetX = static_cast<int>(radiusInPixels * cos(theta));
    int offsetY = static_cast<int>(radiusInPixels * sin(theta));
    return sf::Vector2i(point.x + offsetX, point.y + offsetY);
}

sf::Vector2i generateSpacedPositionsAroundPoint(const sf::Vector2i &point, int radiusInPixels, int index, int maxIndex)
{
    double theta = (2 * M_PI) * (static_cast<double>(index + 1) / maxIndex);
    int offsetX = static_cast<int>(radiusInPixels * cos(theta));
    int offsetY = static_cast<int>(radiusInPixels * sin(theta));
    return sf::Vector2i(point.x + offsetX, point.y + offsetY);
}

sf::Vector2f generateRandomDirectionVector()
{
    double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
    return sf::Vector2f(static_cast<float>(cos(theta)), static_cast<float>(sin(theta)));
}

bool isPointNearMonitorEdge(const sf::Vector2i &point, const sf::Vector2u &windowSize)
{
    constexpr int offset = 50;
    return (point.x - offset <= 0 || point.y - offset <= 0 ||
            point.x + windowSize.x + offset >= screenSize.x ||
            point.y + windowSize.y + offset >= screenSize.y);
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

void saveHighscore(int highscore)
{
    std::ofstream file("saveData.txt");
    if (file.is_open())
    {
        file << highscore;
        file.close();
    }
}

int loadHighscore()
{
    std::ifstream file("saveData.txt");
    int data = 0;
    if (file.is_open())
    {
        file >> data;
        file.close();
    }
    return data;
}
