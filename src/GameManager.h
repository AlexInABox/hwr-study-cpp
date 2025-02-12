#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

class GameManager {
public:
    static bool threadActive;
    static bool threadDone;
    static void Start();
    static void Stop();
};

#endif // GAME_MANAGER_H
