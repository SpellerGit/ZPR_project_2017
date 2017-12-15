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
/*Class that contains all the information about current game
 seession used by gamewindow and gameloop */
class GameData
{
public:
    GameData();
    movingItem* addBullet(int x,
                          int y);
    void setAction(user_action a);
    void releaseAction(user_action a);
//private: //public only for early testing/developing
    movingItem * player; //raw pointer because handled as part of scene
    std::vector<user_action*> actions;
    std::vector<mapItem*> tiles;
    std::vector<movingItem*> bullets;


};

} // namespace game

#endif // GAMEDATA_H
