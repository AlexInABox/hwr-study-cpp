#include "Utilities.hpp"
#include "Textures.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>

const sf::Vector2u screenSize = sf::VideoMode::getDesktopMode().size;

sf::Vector2i generateRandomPositionOnScreenWithPadding(int padding) {
    return sf::Vector2i(rand() % (screenSize.x - padding),
                        rand() % (screenSize.y - padding));
}

sf::Vector2i generateRandomPositionAroundPoint(const sf::Vector2i &point, const int radiusInPixels) {
    const double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
    const int offsetX = static_cast<int>(radiusInPixels * cos(theta));
    const int offsetY = static_cast<int>(radiusInPixels * sin(theta));
    return sf::Vector2i(point.x + offsetX, point.y + offsetY);
}

sf::Vector2i
generateSpacedPositionsAroundPoint(const sf::Vector2i &point, int radiusInPixels, int index, int maxIndex) {
    const double theta = (2 * M_PI) * (static_cast<double>(index + 1) / maxIndex);
    const int offsetX = static_cast<int>(radiusInPixels * cos(theta));
    const int offsetY = static_cast<int>(radiusInPixels * sin(theta));
    return sf::Vector2i(point.x + offsetX, point.y + offsetY);
}

sf::Vector2f generateRandomDirectionVector() {
    const double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
    return sf::Vector2f(static_cast<float>(cos(theta)), static_cast<float>(sin(theta)));
}

bool isPointNearMonitorEdge(const sf::Vector2i &point, const sf::Vector2u &windowSize) {
    constexpr int offset = 50;
    return (point.x - offset <= 0 || point.y - offset <= 0 ||
            point.x + windowSize.x + offset >= screenSize.x ||
            point.y + windowSize.y + offset >= screenSize.y);
}

sf::Vector2f normalize(const sf::Vector2f &v) {
    const float length = std::sqrt(v.x * v.x + v.y * v.y);
    return (length > 0) ? sf::Vector2f(v.x / length, v.y / length) : sf::Vector2f(1.f, 0.f);
}

sf::Vector2f reflectDirection(const sf::Vector2i &position, const sf::Vector2u &windowSize, sf::Vector2f direction) {
    const double theta = static_cast<double>(rand()) / RAND_MAX * 2 * M_PI;
    if (position.x <= 0 || position.x + 50 + windowSize.x >= screenSize.x) {
        direction.x = -direction.x;
        direction.y += static_cast<float>(sin(theta));
    }
    if (position.y <= 0 || position.y + 50 + windowSize.y >= screenSize.y) {
        direction.y = -direction.y;
        direction.x += static_cast<float>(cos(theta));
    }
    return normalize(direction);
}

void saveHighscore(int highscore) {
    std::ofstream file("saveData.txt");
    if (file.is_open()) {
        file << highscore;
        file.close();
    }
}

int loadHighscore() {
    std::ifstream file("saveData.txt");
    int data = 0;
    if (file.is_open()) {
        file >> data;
        file.close();
    }
    return data;
}

sf::Texture popup_1_texture = sf::Texture(__1_png, __1_png_len);
sf::Texture popup_2_texture = sf::Texture(__2_png, __2_png_len);
sf::Texture popup_3_texture = sf::Texture(__3_png, __3_png_len);
sf::Texture popup_4_texture = sf::Texture(__4_png, __4_png_len);
sf::Texture popup_5_texture = sf::Texture(__5_png, __5_png_len);
sf::Texture popup_6_texture = sf::Texture(__6_png, __6_png_len);
sf::Texture popup_7_texture = sf::Texture(__7_png, __7_png_len);
sf::Texture popup_8_texture = sf::Texture(__8_png, __8_png_len);
sf::Texture popup_9_texture = sf::Texture(__9_png, __9_png_len);
sf::Texture popup_10_texture = sf::Texture(__10_png, __10_png_len);
sf::Texture popup_11_texture = sf::Texture(__11_png, __11_png_len);
sf::Texture popup_12_texture = sf::Texture(__12_png, __12_png_len);
sf::Texture popup_13_texture = sf::Texture(__13_png, __13_png_len);
sf::Texture popup_14_texture = sf::Texture(__14_png, __14_png_len);
sf::Texture popup_15_texture = sf::Texture(__15_png, __15_png_len);
sf::Texture popup_16_texture = sf::Texture(__16_png, __16_png_len);
sf::Texture popup_17_texture = sf::Texture(__17_png, __17_png_len);
sf::Texture *popup_textures[] = {
    &popup_1_texture, &popup_2_texture, &popup_3_texture, &popup_4_texture, &popup_5_texture, &popup_6_texture,
    &popup_7_texture, &popup_8_texture, &popup_9_texture, &popup_10_texture, &popup_11_texture, &popup_12_texture,
    &popup_13_texture, &popup_14_texture, &popup_15_texture, &popup_16_texture, &popup_17_texture
};

sf::Texture getRandomPopUpTexture() {
    return *popup_textures[rand() % 17];
}
