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
    for(auto j : data->getPlayers())
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
        //data->players[1]->actions.clear();
        emit loopSignal();
        handleMovement(); //is that not risky (rw conflict) to do that in this async way?

}

void GameLoop::handleMovement()
{
    for(auto &i : data->getPlayers())
    i->move();


    if(!data->getBullets().empty())
    {
        for(int i =0; i<data->getBullets().size(); i++)
        {
            data->getBullets()[i]->move();
            //delete objects if they go too far
            if(data->getBullets()[i]->x()>10000 || data->getBullets()[i]->x()<-500
                    || data->getBullets()[i]->y()>10000 || data->getBullets()[i]->y()<-5000
                    || data->getBullets()[i]->hitPoints<=0)
            data->removeBullet(i);
        }
    }

}

void GameLoop::addNetUserAction(game::user_action a)
{
    qDebug() <<"ADD action " <<a;
    if(a == RELEASE_JUMP)
        data->getPlayers()[1]->releaseAction(JUMP);
    else if(a == RELEASE_LEFT)
        data->getPlayers()[1]->releaseAction(MOVE_LEFT);
    else if(a == RELEASE_RIGHT)
        data->getPlayers()[1]->releaseAction(MOVE_RIGHT);
    else
    data->getPlayers()[1]->setAction(a);
}

void GameLoop::setConnection()
{
    netGame = true;
}

GameLoop::~GameLoop()
{

}

} // namespace game
