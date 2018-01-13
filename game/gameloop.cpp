#include "gameloop.h"
#include <thread>
#include <qdebug.h>
#include <QTimer>
#include <memory>
#include "game/gamewindow.h"

namespace game { //TODO change all those numbers in this class to variables

GameLoop::GameLoop(std::shared_ptr<GameData> gamedata,
                   GameWindow * gamewindpow_ptr)
            : data(gamedata), gamewindow(gamewindpow_ptr)
{
    netGame = false;
    connect(this, SIGNAL(loopSignal()),
            gamewindow, SLOT(updateDisplay()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(40);
}

void GameLoop::run()
{
    if(netGame)
        for(int i =0; i<data->players[0]->actions.size(); i++)
            emit sendUserAction(*data->players[0]->actions[i]);

    for(auto j : data->players)
        if(!j->actions.empty())
            for(auto &i : j->actions)
                switch(*i)
                {
                    case MOVE_LEFT:
                        j->accelerate(-5);
                        break;
                    case MOVE_RIGHT:
                        j->accelerate(5);
                        break;
                    case JUMP:
                        j->jump();
                        break;
                    case SHOOT:
                        break;
                    default:
                        break;
                }

        emit loopSignal();
        handleMovement(); //is that not risky (rw conflict) to do that in this async way?

}

void GameLoop::handleMovement()
{
    for(auto &i : data->players)
    i->move();


    if(!data->bullets.empty())
    {
        for(int i =0; i<data->bullets.size(); i++)
        {
            data->bullets[i]->move();
            //delete objects if they go too far
            if(data->bullets[i]->x()>10000 || data->bullets[i]->x()<-500
                    || data->bullets[i]->y()>10000 || data->bullets[i]->y()<-5000
                    || data->bullets[i]->hitPoints<=0)
            data->bullets.erase(data->bullets.begin()+i);
        }
    }

}

void GameLoop::addNetUserAction(game::user_action a)
{
    data->players[1]->setAction(a);
}

void GameLoop::setConnection(std::shared_ptr<network::Connection> con)
{
    connection = con;
    netGame = true;
    connect(connection.get(), SIGNAL(receiveAction(game::user_action)),
            this, SLOT(addNetUserAction(game::user_action)));
    connect(this, SIGNAL(sendUserAction(game::user_action)),
            connection.get(), SLOT(sendAction(game::user_action)));

}

GameLoop::~GameLoop()
{

}

} // namespace game
