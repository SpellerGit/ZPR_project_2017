#include "gameloop.h"
#include <thread>
#include <qdebug.h>
#include <QTimer>
#include <memory>
#include "game/gamewindow.h"

namespace game {

GameLoop::GameLoop(std::shared_ptr<GameData> gamedata,
                   GameWindow * gamewindpow_ptr)
            : data(gamedata), gamewindow(gamewindpow_ptr)
{
    connect(this, SIGNAL(mySignal()),
            gamewindow, SLOT(updateDisplay()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(25);
    qDebug() << "timer started";
}

void GameLoop::run()
{
        qDebug() << "running in loop";
        switch(data->action)
        {
            case MOVE_LEFT:
                data->player->accelerate(-2);
                break;
            case MOVE_RIGHT:
                data->player->accelerate(2);
                break;
            case JUMP:
                data->player->jump();
                break;
            case SHOOT:
                break;
            default:
                break;
        }

        handleMovement();

        data->action = IDLE;
        emit mySignal();
}

void GameLoop::handleMovement()
{
    //do this for each moving object?
    //Also check for collisions, here or in move method?
    data->player->move();


    if(!data->bullets.empty())
        for(int i =0; i<data->bullets.size(); i++)
        {
            data->bullets[i]->move();
            //delete objects if they go too far
            if(data->bullets[i]->posX>10000 || data->bullets[i]->posX<-500
                    || data->bullets[i]->posY>10000 || data->bullets[i]->posY<-500)
            data->bullets.erase(data->bullets.begin()+i);

        }

}

GameLoop::~GameLoop()
{

}

} // namespace game
