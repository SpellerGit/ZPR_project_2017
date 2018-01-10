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
    connect(this, SIGNAL(mySignal()),
            gamewindow, SLOT(updateDisplay()));

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(run()));
    timer->start(40);
}

void GameLoop::run()
{
    if(!data->actions.empty())
    for(auto &i : data->actions)
        switch(*i)
        {
            case MOVE_LEFT:
                data->player->accelerate(-5);
                break;
            case MOVE_RIGHT:
                data->player->accelerate(5);
                break;
            case JUMP:
                data->player->jump();
                break;
            case SHOOT:
                break;
            default:
                break;
        }

        emit mySignal();
        handleMovement(); //is that not risky (rw conflict) to do that in this async way?

}

void GameLoop::handleMovement()
{
    data->player->move();


    if(!data->bullets.empty())
    { //qDebug() << " bullets number : " << data->bullets.size(); //delete later
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

GameLoop::~GameLoop()
{

}

} // namespace game
