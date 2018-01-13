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
    if(connection)
        loop->setNetGame();
    gamewindow->show();
    qDebug() << "to run loop";

    if(connection)
        setupConnection();

}

void GameManager::startGame(std::shared_ptr<game::GameData> gamedata)
{
    qDebug() << "to make loop";
    gamewindow = new GameWindow();
    gamewindow->setData(gamedata);

    loop = new GameLoop(gamedata,gamewindow);
    gamewindow->show();
    qDebug() << "to run loop";

    if(connection)
        setupConnection();
}

void GameManager::setConnection(std::shared_ptr<network::Connection> con)
{
    connection = con;
    setupConnection();
}

void GameManager::setupConnection()
{
    connect(connection.get(), SIGNAL(receiveAction(user_action a)),
            loop, SLOT(addNetUserAction(user_action a)));
    connect(loop, SIGNAL(sendUserAction(user_action a)),
            connection.get(), SLOT(sendAction(user_action a)));
    connect(connection.get(), SIGNAL(startGame()),
            this, SLOT(startGame));

}


} // namespace game
