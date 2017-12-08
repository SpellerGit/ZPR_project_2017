#include "gameloop.h"
#include <thread>
#include <qdebug.h>
#include <utility>
#include <memory>
#include <windows.h>
#include "game/gamewindow.h"

namespace game {

GameLoop::GameLoop(std::shared_ptr<GameData> gamedata, std::function<void()> updatecb)
            : data(gamedata), updateDisplay(updatecb) {}
//{
    //potentially we may want to make a thread here to run the loop?
 //     data(std::move(gamedata));
//}

void GameLoop::run()
{
    while(true)
    {
        qDebug() << "running in loop";
        switch(data->action)
        {
            case MOVE_LEFT:
                data->player->posX--;  //should be  data->player->moveLeft() or move(angle) or smth
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
       // updateDisplay();
        Sleep(500); //IMPORTANT, keep in mind that sleep is windows function and wont work on linux
                    //on linux we acn usleep or whatever, so need to ifdef this most likely
    }
}

GameLoop::~GameLoop()
{

}

} // namespace game
