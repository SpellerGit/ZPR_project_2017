#include "gamemanager.h"
#include <QDebug>
#include <functional>
#include <QThreadPool>
#include <Windows.h>

namespace game {

GameManager::~GameManager()
{
    delete loop;
    delete gamewindow;
    qDebug() <<"FDGD";
}

void GameManager::startGame()
{
    gamedata = std::shared_ptr<GameData>(new GameData()); // set gamedata? it gotta be created earlier btw
    qDebug() << "to make loop";
    gamewindow = new GameWindow();
    gamewindow->setData(gamedata);

    loop = new GameLoop(gamedata,gamewindow);
    gamewindow->show();
    qDebug() << "to run loop";
}


} // namespace game
