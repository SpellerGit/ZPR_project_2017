#include "gamedata.h"
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <math.h>

namespace game {
/* This class will be keeping whole the game data, and
 * proporties/values, like map, players etc
 */
GameData::GameData()
{
   QImage image(":/images/image3.png");
   player = new movingItem();
   player->setPixmap(QPixmap::fromImage(image));
   player->posX=100;
   player->posY=500;
  // player->setPos(0,0);

   QImage image2(":/images/image1.png");
   background = new movingItem();
   background->setPixmap(QPixmap::fromImage(image2));
    //TODO create map factory class, create iitem factory

    action = IDLE; //delete this when default values are handled... or smth

    bullet = nullptr;
}

void GameData::setShootingPos(int x, int y)
{
    action = SHOOT;
    shootPointX = x;
    shootPointY = y;
}

void GameData::addBullet() //first prototype version, must get much more customizable in future
{
    if(bullet)
        delete bullet;


    qDebug() << "addBullet";

    float diffX = abs(shootPointX-player->posX);
    float diffY = abs(shootPointY-player->posY);

    float ratio = diffX/(diffX+diffY); //i am doing this to get angle at which the bullet is shot

    float speedx = ratio*100;
    float speedy = (ratio-1)*100;

    qDebug() << "diffX " <<diffX;
    qDebug() << "diffY " <<diffY;
    qDebug() << "RATIO " <<ratio;
    qDebug() << "speedx " << speedx;
    qDebug() << "speedy " << speedy;

    bullet = new movingItem((int)speedx,(int)speedy,player->posX,player->posY);

    QImage image(":/images/bullet.png");
    bullet->setPixmap(QPixmap::fromImage(image));

}


} // namespace game
