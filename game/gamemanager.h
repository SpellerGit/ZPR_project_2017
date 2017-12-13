#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "game/gamewindow.h"
#include "game/gameloop.h"

namespace game {

class GameManager
{
public:
    ~GameManager();
    void startGame();
    void startGame(std::shared_ptr<GameData> gamedata);


private:
    //std::shared_ptr<GameWindow> gamewindow;
    GameWindow * gamewindow;
    std::shared_ptr<GameData> gamedata;
   // std::unique_ptr<GameLoop> loop;
    GameLoop * loop;

};

} // game

#endif // GAMEMANAGER_H
