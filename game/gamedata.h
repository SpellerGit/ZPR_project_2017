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
        SHOOT,
        IDLE
};

class GameData
{
public:
    GameData();
    void setShootingPos(int x, int y);
    void addBullet();

//private: //public only for early testing/developing
    movingItem * player; //raw pointer because handled as part of scene
    movingItem * background;
    user_action action;
    movingItem * bullet;

    int shootPointX;
    int shootPointY;

};

} // namespace game

#endif // GAMEDATA_H
