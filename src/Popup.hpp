#ifndef WINDOW_MANAGER_HPP
#define WINDOW_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Sounds.hpp"


/**
 * @brief A custom wrapper for a PopUp window in the game. Each instance of this class manages a single popup window.
 */
class Popup {
public:
    /**
     * @brief Constructs a PopUp with random properties.
     */
    Popup();

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

    /**
     * @brief Close the popup and play a sound.
     */
    void loudClose();

private:
    sf::RenderWindow currentWindow; ///< Reference to the SFML render window.
    int randomNumber; ///< Random number that dictates the window's properties.
    const std::vector<std::u32string> popupTitles = {
        U"🚨 WARNING: Your PC is Infected!",
        U"💰 YOU WON $1,000,000! 🎉",
        U"🔥 HACKER ALERT! Change Passwords!",
        U"🖥️ Free RAM Upgrade! 🆓 Click now!",
        U"📢 You are the 1,000,000th visitor! 🎯",
        U"🔞 HOT Singles in Your Area! 💋",
        U"🔋 Battery Virus Detected! ⚠️ Fix now!",
        U"🎮 FREE ROBUX? ⚡ Get before it's gone!",
        U"💾 Windows Needs an Urgent Update! ⏳",
        U"🐱‍💻 AI Detected You! Solve CAPTCHA Now!",
        U"💻 System Overload! Click to Fix Instantly!",
        U"🎁 You Won a FREE iPhone 20 Pro Ultra! 📱",
        U"⚠️ FBI Alert: Illegal Browsing Detected! 🚔",
        U"💀 CRITICAL ERROR: Your PC is DYING! ☠️",
        U"🤖 Virus.exe is now controlling your mouse! 🕷️"
    }; ///< List of popup titles.
    sf::Texture randomTexture;
    sf::SoundBuffer dismissSoundBuffer{dismissPopUp_wav, dismissPopUp_wav_len};
    sf::Sound dismissSound{dismissSoundBuffer};
    sf::SoundBuffer openSoundBuffer{openPopUp_wav, openPopUp_wav_len};
    sf::Sound openSound{openSoundBuffer};
};

#endif // WINDOW_MANAGER_HPP
