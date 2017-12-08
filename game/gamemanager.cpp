#include "gamemanager.h"
#include <QDebug>
#include <functional>
#include <QtConcurrent/QtConcurrent>
#include <QThreadPool>
#include <Windows.h>

namespace game {

GameManager::~GameManager()
{
    delete loop;
    qDebug() <<"FDGD";
}

void GameManager::startGame()
{
    gamedata = std::shared_ptr<GameData>(new GameData()); // set gamedata? it gotta be created earlier btw
    qDebug() << "to make loop";
    gamewindow = std::unique_ptr<GameWindow>(new GameWindow());
    gamewindow->setData(gamedata);
    loop = new GameLoop
                     (gamedata,std::bind(&GameWindow::update, gamewindow));
    gamewindow->show();
    qDebug() << "to run loop";
    QThreadPool::globalInstance()->start(loop);

}


} // namespace game
