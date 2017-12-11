#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <qgraphicsscene.h>
#include <memory>
#include "game/mapitem.h"
#include "game/movingitem.h"

namespace game{

enum user_action {
        MOVE_LEFT,
        MOVE_RIGHT,
        JUMP,
        SHOOT
};

class GameData
{
public:
    GameData();

//private: //public only for early testing/developing
    movingItem * player; //raw pointer because handled as part of scene
    movingItem * background; //temporary object rather i suppose
    user_action action;
    std::vector<mapItem> items;
   // std::shared_ptr<GameWindow> gwindow;
    //also some map object here i recon

};

} // namespace game

#endif // GAMEDATA_H
