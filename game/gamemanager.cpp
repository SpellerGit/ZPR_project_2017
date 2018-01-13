#include "gamemanager.h"
#include "gameloop.h"
#include <QDebug>
#include <functional>
#include <QThreadPool>
#include <algorithm>

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
    loop->setConnection();
    connection = con;
    setupConnection();
}

void GameManager::setupConnection()
{
    connect(connection.get(), SIGNAL(startGameSignal(QString)),
            this, SLOT(showGame(QString)));

    connect(connection.get(), SIGNAL(receiveAction(game::user_action)),
            loop, SLOT(addNetUserAction(game::user_action)));

    connect(gamewindow, SIGNAL(sendUserAction(game::user_action)),
            connection.get(), SLOT(sendAction(game::user_action)));
}

void GameManager::showGame(QString type)
{
    qDebug() << "showing da game as " <<type;
    if(type=="CLIENT")
    {
        auto tmp = gamedata->players[0];
        gamedata->players.erase(gamedata->players.begin());
        gamedata->players.push_back(tmp);
    }
    qDebug() << "xdd";
    gamewindow->show();
}


} // namespace game
