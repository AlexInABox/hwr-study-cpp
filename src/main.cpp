#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <string>
#include <thread>
#include "BerlinTypeOffice.hpp"
#include "Textures.hpp"
#include "WindowManager.h"
#include "Utilities.h"

sf::Font fontRegular;
sf::Font fontBold;
sf::Text startButton(fontRegular, ""), exitButton(fontRegular, "");
std::vector<sf::Text *> menuButtons;
int selectedIndex = 0;
sf::Texture alien_1_texture, alien_2_texture, alien_3_texture, alien_4_texture, alien_5_texture;

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
    // Load font

    (void)fontRegular.openFromMemory(&BerlinTypeOffice_Regular_ttf, BerlinTypeOffice_Regular_ttf_len);
    (void)fontBold.openFromMemory(&BerlinTypeOffice_Bold_ttf, BerlinTypeOffice_Bold_ttf_len);

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

sf::RenderWindow menuWindow = sf::RenderWindow(sf::VideoMode({600u, 450u}), "Dodge the uh.. windows. :3", sf::Style::Default);

std::vector<std::thread> active_windows_threads;
std::vector<WindowManager> active_windowManagers;
std::vector<sf::RenderWindow> active_windows;
void StartThreadForGame()
{

    // Set up some windows
    for (int i = 0; i < 30; i++)
    {
        active_windows.push_back(sf::RenderWindow(sf::VideoMode({100u, 100u}), "", sf::Style::None));
        active_windowManagers.push_back(WindowManager());
        active_windowManagers[i].currentWindow = active_windows[i];
    }
    sf::Vector2i mousePosition = sf::Mouse::getPosition();
    for (int i = 0; i < active_windows.size(); i++)
    {
        active_windows[i].setPosition(UTILITIES_HPP::generateSpacedPositionsAroundPoint(mousePosition, 500, i, active_windows.size()));
        active_windows[i].setFramerateLimit(30);
    }

    for (int i = 0; i < active_windows.size(); i++)
    {
        }

    std::cout << "GameManager launched.\n";
}

void Exit()
{
    for (int i = 0; i < active_windows_threads.size(); i++)
    {
        active_windows_threads[i].join();
    }
    GameManager::Stop();
}

void handleKeyboardEvent(sf::RenderWindow &menuWindow, sf::Keyboard::Key key)
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
            StartThreadForGame();
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

    while (menuWindow.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        while (const std::optional event = menuWindow.pollEvent())
        {
            // "close requested" event: we close the window
            if (event->is<sf::Event::Closed>())
            {
                Exit();
            }
            else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                handleKeyboardEvent(menuWindow, keyPressed->code);
            }
        }

        menuWindow.clear(sf::Color(0, 81, 186));

        for (int i = 0; i < menuButtons.size(); ++i)
        {
            menuWindow.draw(*menuButtons[i]);
        }

        menuWindow.draw(alien_1_sprite);
        menuWindow.draw(alien_2_sprite);
        menuWindow.draw(alien_3_sprite);
        menuWindow.draw(alien_4_sprite);
        menuWindow.draw(alien_5_sprite);
        menuWindow.display();
    }
}