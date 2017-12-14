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
   player->posY=574;

   QImage image2(":/images/background1.bmp");
   background = new movingItem();
   background->setPixmap(QPixmap::fromImage(image2));

   QImage image3(":/images/tile1.bmp");
  // auto tile = new mapItem();
  // tile->setPixmap(QPixmap::fromImage(image3));
  // tile->posX=485;
  // tile->posY=600;

   int i =0;


   //Creating some first test map, best to ignore this...

   mapItem * tile = new movingItem();
   tile->setPixmap(QPixmap::fromImage(image3));
   tile->posX=0;
   tile->posY=550;
   tiles.push_back(tile);

   mapItem * tile2 = new movingItem();
   tile2->setPixmap(QPixmap::fromImage(image3));
   tile2->posX=600;
   tile2->posY=550;
   tiles.push_back(tile2);

   mapItem * tile4 = new movingItem();
   tile4->setPixmap(QPixmap::fromImage(image3));
   tile4->posX=650;
   tile4->posY=550;
   tiles.push_back(tile4);

   mapItem * tile5 = new movingItem();
   tile5->setPixmap(QPixmap::fromImage(image3));
   tile5->posX=700;
   tile5->posY=550;
   tiles.push_back(tile5);

   mapItem * tile3 = new movingItem();
   tile3->setPixmap(QPixmap::fromImage(image3));
   tile3->posX=0;
   tile3->posY=650;
   tiles.push_back(tile3);


   mapItem * tile6 = new movingItem();
   tile6->setPixmap(QPixmap::fromImage(image3));
   tile6->posX=750;
   tile6->posY=500;
   tiles.push_back(tile6);
   while(true)
   {
       mapItem * tile = new movingItem();
       tile->setPixmap(QPixmap::fromImage(image3));
       tile->posX=i;
       tile->posY=600;

       tiles.push_back(tile);

       qDebug() << "Created TILE!";

       i+=50;
       if(i>600)
           break;
   }
i=0;
   while(true)
   {
       mapItem * tile = new movingItem();
       tile->setPixmap(QPixmap::fromImage(image3));
       tile->posX=i;
       tile->posY=700;

       tiles.push_back(tile);

       qDebug() << "Created TILE!";

       i+=50;
       if(i>1000)
           break;
   }

   bullets = std::vector<movingItem*>(); //gotta init it somewhere...
   action = IDLE; //delete this when default values are handled... or smth

}

movingItem* GameData::addBullet(int shootPointX,
                                 int shootPointY)
                                          //first prototype version, must get much more customizable in future
                                          //Also cleaner
{
    action = SHOOT;

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

    float speedx = ratio*75 * tempx;
    float speedy = (1-ratio)*75 * tempy;

  /*  qDebug() << "diffX " <<diffX;
    qDebug() << "diffY " <<diffY;
    qDebug() << "RATIO " <<ratio;   LOGS
    qDebug() << "speedx " << speedx;
    qDebug() << "speedy " << speedy;*/

    movingItem * bullet = new movingItem((int)speedx,(int)speedy,player->posX,player->posY);

    QImage image(":/images/bullet.png");
    bullet->setPixmap(QPixmap::fromImage(image));

    return bullet;

}


} // namespace game
