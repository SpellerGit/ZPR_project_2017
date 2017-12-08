#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <thread>
#include <functional>
#include "game/gamedata.h"
#include <qgraphicsscene.h>
#include <QRunnable>

namespace game {

//Should this be here btw?

class GameLoop : public QRunnable
{
public:
    GameLoop(std::shared_ptr<GameData> gamedata, std::function<void()> updatecb);
    ~GameLoop();
    void run();

private:
    bool running; // is this the way to go? consider this/other ways to do it
    std::shared_ptr<GameData> data;
    std::function<void()> updateDisplay;
};

} //namespace game

#endif // GAMELOOP_H
