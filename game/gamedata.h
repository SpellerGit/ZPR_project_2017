#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <qgraphicsscene.h>
#include <memory>
#include "game/mapitem.h"
#include "game/movingitem.h"

namespace game{

/**
 * Class that contains all the information about current game
 * seession used by gamewindow and gameloop
 */
class GameData
{
public:
    GameData();
    movingItem* addBullet(int x,
                          int y,
                          int playerNumber);
    void insertBullet(movingItem * bullet);
    void removeBullet(int index);
    std::vector<movingItem*> getPlayers() const;
    std::vector<movingItem*> getBullets() const;
    std::vector<mapItem*> getTiles() const;

private:
    std::vector<movingItem*> players;
    std::vector<mapItem*> tiles;
    std::vector<movingItem*> bullets;


};

} // namespace game

#endif // GAMEDATA_H
