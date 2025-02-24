#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include "BerlinTypeOffice.hpp"
#include "Textures.hpp"
#include "WindowManager.hpp"
#include "Utilities.hpp"
#include <algorithm> // Required for std::remove_if (C++17 and earlier)
#include <cmath>

sf::Font fontRegular;
sf::Font fontBold;
sf::Text startButton(fontRegular, ""), exitButton(fontRegular, "");
std::vector<sf::Text *> menuButtons;
int selectedIndex = 0;
sf::Texture alien_1_texture, alien_2_texture, alien_3_texture, alien_4_texture, alien_5_texture;
sf::Image icon;

void setupTextures()
{

    (void)alien_1_texture.loadFromMemory(__1_alien_png, __1_alien_png_len);
    (void)alien_2_texture.loadFromMemory(__2_alien_png, __2_alien_png_len);
    (void)alien_3_texture.loadFromMemory(__3_alien_png, __3_alien_png_len);
    (void)alien_4_texture.loadFromMemory(__4_alien_png, __4_alien_png_len);
    (void)alien_5_texture.loadFromMemory(__5_alien_png, __5_alien_png_len);
}

void setupSprites(sf::RenderWindow &menuWindow, sf::Sprite *alien_sprites[])
{
    sf::Texture *alien_textures[] = {&alien_1_texture, &alien_2_texture, &alien_3_texture, &alien_4_texture, &alien_5_texture};

    for (int i = 0; i < 5; ++i)
    {
        alien_sprites[i]->setScale({0.28f, 0.28f});
        alien_sprites[i]->setOrigin({0.f, static_cast<float>(alien_textures[i]->getSize().y)});
        alien_sprites[i]->setPosition({5.f + (i * 120), static_cast<float>(menuWindow.getSize().y) + 0});
    }

    alien_sprites[2]->setScale({0.43f, 0.43f});
    alien_sprites[2]->setPosition({5.f + 220, static_cast<float>(menuWindow.getSize().y) + 30});

    alien_sprites[3]->setScale({0.40f, 0.40f});
    alien_sprites[3]->setPosition({5.f + 350, static_cast<float>(menuWindow.getSize().y) + 30});
}

void setupMenu(sf::RenderWindow &menuWindow)
{
    menuWindow.setVerticalSyncEnabled(true);
    menuWindow.setFramerateLimit(0);
    menuWindow.setKeyRepeatEnabled(false);
    // Load font

    (void)fontRegular.openFromMemory(&BerlinTypeOffice_Regular_ttf, BerlinTypeOffice_Regular_ttf_len);
    (void)fontBold.openFromMemory(&BerlinTypeOffice_Bold_ttf, BerlinTypeOffice_Bold_ttf_len);

    // Load Icons

    (void)icon.loadFromMemory(logo_full_1to1_png, logo_full_1to1_png_len);
    menuWindow.setIcon(icon);

    // Configure buttons
    startButton.setFont(fontBold);
    startButton.setString("Start");
    startButton.setCharacterSize(30);
    startButton.setFillColor(sf::Color::White);
    startButton.setPosition({50.f, 100.f});

    exitButton.setFont(fontRegular);
    exitButton.setString("Exit");
    exitButton.setCharacterSize(30);
    exitButton.setFillColor(sf::Color::White);
    exitButton.setPosition({50.f, 150.f});

    menuButtons = {&startButton, &exitButton};
    menuButtons[selectedIndex]->setFillColor(sf::Color(255, 218, 26)); // Highlight first button
}

sf::RenderWindow menuWindow = sf::RenderWindow(sf::VideoMode({600u, 450u}), "Dismiss the PopUps!", sf::Style::Default);
bool gameIsRunning = false;
sf::Clock levelClock;  // Timer for level increase
sf::Clock globalTimer; // Timer for level increase

std::vector<std::unique_ptr<WindowManager>> active_windowManagers;
std::vector<sf::RenderWindow> active_windows;

void StartGame()
{
    gameIsRunning = true;

    menuButtons[selectedIndex]->setFillColor(sf::Color::White);
    selectedIndex = (selectedIndex + 1) % menuButtons.size();
    menuButtons[selectedIndex]->setFillColor(sf::Color::Yellow);

    levelClock.restart();
    globalTimer.restart();

    std::cout << "GameManager launched.\n";
}

void spawnNewPopUp()
{
    // https://www.geeksforgeeks.org/how-to-remove-an-element-from-vector-in-cpp/
    active_windowManagers.erase(
        std::remove_if(active_windowManagers.begin(), active_windowManagers.end(),
                       [](const std::unique_ptr<WindowManager> &wm)
                       { return wm->isClosed; }),
        active_windowManagers.end());

    active_windowManagers.push_back(std::make_unique<WindowManager>());
}

void Exit()
{
    menuWindow.close();

    for (auto &manager : active_windowManagers)
    {
        manager->forceClose();
    }
}

void handleKeyboardEvent(sf::RenderWindow &menuWindow)
{
    sf::Keyboard::Key key;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        key = sf::Keyboard::Key::Up;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        key = sf::Keyboard::Key::Down;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
        key = sf::Keyboard::Key::Enter;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        key = sf::Keyboard::Key::Space;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        key = sf::Keyboard::Key::Escape;

    if (key == sf::Keyboard::Key::Enter || key == sf::Keyboard::Key::Space || key == sf::Keyboard::Key::Escape)
    {
        Exit();
    }
}

void handleExpensiveKeyboardEvent(sf::RenderWindow &menuWindow, sf::Keyboard::Key key)
{
    if (key == sf::Keyboard::Key::Up)
    {
        menuButtons[selectedIndex]->setFillColor(sf::Color::White);
        selectedIndex = (selectedIndex - 1 + menuButtons.size()) % menuButtons.size();
        menuButtons[selectedIndex]->setFillColor(sf::Color::Yellow);
    }
    else if (key == sf::Keyboard::Key::Down)
    {
        menuButtons[selectedIndex]->setFillColor(sf::Color::White);
        selectedIndex = (selectedIndex + 1) % menuButtons.size();
        menuButtons[selectedIndex]->setFillColor(sf::Color::Yellow);
    }
    else if (key == sf::Keyboard::Key::Enter || key == sf::Keyboard::Key::Space)
    {
        if (menuButtons[selectedIndex]->getString() == "Start")
        {
            StartGame();
        }
        else if (menuButtons[selectedIndex]->getString() == "Exit")
        {
            Exit();
        }
    }
    else if (key == sf::Keyboard::Key::Escape)
    {
        Exit();
    }
}

int main()
{

    setupMenu(menuWindow);
    setupTextures();
    sf::Sprite alien_1_sprite(alien_1_texture);
    sf::Sprite alien_2_sprite(alien_2_texture);
    sf::Sprite alien_3_sprite(alien_3_texture);
    sf::Sprite alien_4_sprite(alien_4_texture);
    sf::Sprite alien_5_sprite(alien_5_texture);
    sf::Sprite *alien_sprites[] = {&alien_1_sprite, &alien_2_sprite, &alien_3_sprite, &alien_4_sprite, &alien_5_sprite};
    setupSprites(menuWindow, alien_sprites);

    int level = 1;
    float spawnInterval = 2.5f;   // The intervall at which to increase the level
    const int eventInterval = 10; // Every x levels spawn an event or increase the amount of spawned popups
    int amountOfPopUpsToSpawnPerLevel = 1;

    int highscore = loadHighscore();

    while (menuWindow.isOpen())
    {
        if (gameIsRunning)
        {
            float elapsedTime = levelClock.getElapsedTime().asSeconds();

            if (elapsedTime >= spawnInterval)
            {
                level++;
                levelClock.restart();

                if (level % eventInterval == 0)
                {
                    amountOfPopUpsToSpawnPerLevel++;
                    spawnInterval += 0.75f;
                }

                for (int i = 0; i < amountOfPopUpsToSpawnPerLevel; i++)
                {
                    spawnNewPopUp();
                }

                for (auto &manager : active_windowManagers)
                {
                    manager->unHide();
                }
            }
        }

        while (const std::optional event = menuWindow.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                menuWindow.close();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                handleExpensiveKeyboardEvent(menuWindow, keyPressed->code);
            }
        }

        menuWindow.clear(sf::Color(0, 81, 186));

        if (!gameIsRunning)
        {
            for (int i = 0; i < menuButtons.size(); ++i)
            {
                menuWindow.draw(*menuButtons[i]);
            }
        }
        else
        {
            for (int i = 1; i < menuButtons.size(); ++i)
            {
                menuWindow.draw(*menuButtons[i]);
            }
        }

        // Game Statistics
        if (gameIsRunning)
        {
            // Base position for stats
            float baseX = menuWindow.getSize().x - 200; // Align to the right
            float baseY = 50;
            float spacing = 40; // Space between stats

            // High Score
            sf::Text stat_highScore(fontBold);
            stat_highScore.setString("Score: " + std::to_string(active_windowManagers.size()));
            stat_highScore.setCharacterSize(24);
            stat_highScore.setPosition(sf::Vector2f(baseX, baseY + 1 * spacing));
            menuWindow.draw(stat_highScore);

            // Speed Level
            sf::Text stat_level(fontBold);
            stat_level.setString("Level: " + std::to_string(level));
            stat_level.setCharacterSize(24);
            stat_level.setPosition(sf::Vector2f(baseX, baseY + 2 * spacing));
            menuWindow.draw(stat_level);

            // Time Survived (if applicable)
            sf::Text stat_time(fontBold);
            stat_time.setString("Time: " + std::to_string(globalTimer.getElapsedTime().asSeconds()) + "s");
            stat_time.setCharacterSize(24);
            stat_time.setPosition(sf::Vector2f(baseX, baseY + 3 * spacing));
            menuWindow.draw(stat_time);
        }

        menuWindow.draw(alien_1_sprite);
        menuWindow.draw(alien_2_sprite);
        menuWindow.draw(alien_3_sprite);
        menuWindow.draw(alien_4_sprite);
        menuWindow.draw(alien_5_sprite);
        menuWindow.display();

        //  MAC ONLY: mousePosition = mousePosition / 2;
        for (auto &manager : active_windowManagers)
        {
            manager->update();
            manager->level = level;
        }
    }
}