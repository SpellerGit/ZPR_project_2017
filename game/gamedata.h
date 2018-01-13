#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <qgraphicsscene.h>
#include <memory>
#include <QWidget>
#include "game/mapitem.h"
#include "game/movingitem.h"

namespace game{

/*Class that contains all the information about current game
 seession used by gamewindow and gameloop */
class GameData : public QWidget
{
public:
    GameData();

    void loadmap(); // adding and modifying maps

    movingItem* addBullet(int x,
                          int y,
                          int playerNumber);

//private: //public only for early testing/developing
    std::vector<movingItem*> players;
    std::vector<mapItem*> tiles;
    std::vector<movingItem*> bullets;
    QString background = ":/images/background1.bmp"; // if player doesnt choose the map , this is basic one


};

} // namespace game

#endif // GAMEDATA_H
