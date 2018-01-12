#include "gamemanager.h"
#include <QDebug>
#include <functional>
#include <QThreadPool>

namespace game {

GameManager::~GameManager()
{
    delete loop;             //How does qt pointers work? Why do we use delete?
    delete gamewindow;       //investigate qpointers

}

void GameManager::startGame() // its loading test map
{

    gamedata = std::shared_ptr<GameData>(new GameData());

    qDebug() << "to make loop";
    gamewindow = new GameWindow();
    gamewindow->setData(gamedata);

    loop = new GameLoop(gamedata,gamewindow);
    gamewindow->show();
    qDebug() << "to run loop";

}


} // namespace game
