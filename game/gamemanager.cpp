#include "gamemanager.h"
#include "gameloop.h"
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

void GameManager::setConnection(std::shared_ptr<network::Connection> con)
{
    gamedata = std::shared_ptr<GameData>(new GameData());

    qDebug() << "to make loop";
    gamewindow = new GameWindow();
    gamewindow->setData(gamedata);

    loop = new GameLoop(gamedata,gamewindow);
    loop->setConnection(con);
    connection = con;
    setupConnection();
}

void GameManager::setupConnection()
{
    connect(connection.get(), SIGNAL(startGameSignal()),
            this, SLOT(showGame()));
}

void GameManager::showGame()
{
    gamewindow->show();
}


} // namespace game
