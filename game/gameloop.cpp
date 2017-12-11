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
    timer->start(50);
    qDebug() << "timer started";
}

void GameLoop::run()
{
        qDebug() << "running in loop";
        switch(data->action)
        {
            case MOVE_LEFT:
                data->player->posX--;
                break;
            case MOVE_RIGHT:
                data->player->posX++;
                break;
            case JUMP:
                break;
            case SHOOT:
                break;
            default:
                break;
        }
        emit mySignal();


}


GameLoop::~GameLoop()
{

}

} // namespace game
