#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "game/gamewindow.h"
#include "game/gameloop.h"
#include "QPointer"

namespace game {
/*Class that is called from menu when game is to begin*/
class GameManager
{
public:
    ~GameManager();
    void startGame();
    void startGame(std::shared_ptr<GameData> gamedata);


private:
    QPointer<GameWindow> gamewindow; //regular c++ smart pointers arent working for Q_OBjects
    std::shared_ptr<GameData> gamedata;
    GameLoop * loop; //why if we use qpointer it would not work?

};

} // game

#endif // GAMEMANAGER_H
