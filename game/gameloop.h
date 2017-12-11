#ifndef GAMELOOP_H
#define GAMELOOP_H

#include <thread>
#include <functional>
#include "game/gamedata.h"
#include "game/gamewindow.h"
#include <qgraphicsscene.h>
#include <QRunnable>

namespace game {

class GameLoop : public QObject
{
    Q_OBJECT
public:
    GameLoop(std::shared_ptr<GameData> gamedata,
             GameWindow * gamewindow);
    ~GameLoop();

private:
    std::shared_ptr<GameData> data;
    GameWindow * gamewindow;
    void handleMovement();

signals:
   void mySignal();

private slots:
   void run();

};

} //namespace game

#endif // GAMELOOP_H
