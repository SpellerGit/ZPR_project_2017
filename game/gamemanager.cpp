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

void GameManager::startGame(std::shared_ptr<game::GameData> gamedata)
{

    qDebug() << "to make loop";
    gamewindow = new GameWindow();
    gamewindow->setData(gamedata);

    loop = new GameLoop(gamedata,gamewindow);
    gamewindow->show();
    qDebug() << "to run loop";
}




} // namespace game
