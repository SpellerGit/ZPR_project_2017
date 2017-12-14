#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <qgraphicsscene.h>
#include <memory>
#include <QWidget>
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

class GameData : public QWidget
{
public:
    GameData();

    void loadmap ();
    void insertitems ( int const& index, int const & width, int const& height, int size);
    movingItem* addBullet(int x, int y);

//private: //public only for early testing/developing
    movingItem * player; //raw pointer because handled as part of scene
    movingItem * background;
    user_action action;
    std::vector<mapItem*> tiles; //temporary, for testing
    std::vector<movingItem*> bullets;

    int shootPointX;
    int shootPointY;

};

} // namespace game

#endif // GAMEDATA_H
