#include "gamedata.h"
#include <QImage>
#include <QPixmap>

namespace game {
/* This class will be keeping whole the game data, and
 * proporties/values, like map, players etc
 */
GameData::GameData()
{
    //here maybe we can set gamedata? or finish doing it? Yet to de determined finally
   QImage image(":/images/image3.png");
   player = new movingItem();
   player->setPixmap(QPixmap::fromImage(image));
   player->posX=0;
   player->posY=0;
   player->setPos(0,0);

   QImage image2(":/images/image1.png");
   background = new movingItem();
   background->setPixmap(QPixmap::fromImage(image2));
    //TODO create map factory class, create iitem factory

    action = JUMP; //delete this when defaul values are handled... or smth
}

} // namespace game
