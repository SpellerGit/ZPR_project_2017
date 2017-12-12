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
   player->posX=500;
   player->posY=500;

   QImage image2(":/images/background1.bmp");
   background = new movingItem();
   background->setPixmap(QPixmap::fromImage(image2));

   QImage image3(":/images/tile1.bmp");
   tile = new mapItem();
   tile->setPixmap(QPixmap::fromImage(image3));
   tile->posX=485;
   tile->posY=600;

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

    int tempx=1;
    int tempy=1;

    if(shootPointX-player->posX<0)
        tempx=-1;

    if(shootPointY-player->posY<0)
        tempy=-1;

    float diffX = abs(shootPointX-player->posX);
    float diffY = abs(shootPointY-player->posY); //can user break the game when he presses on himself?
                                                 //we would get zero division maybe we should handle this error

    float ratio = diffX/(diffX+diffY); //i am doing this to get angle at which the bullet is shot

    float speedx = ratio*100 * tempx;
    float speedy = (1-ratio)*100 * tempy;

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
