#include "gamedata.h"
#include <QImage>
#include <QPixmap>
#include <QDebug>
#include <math.h>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>

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
  // auto tile = new mapItem();
  // tile->setPixmap(QPixmap::fromImage(image3));
  // tile->posX=485;
  // tile->posY=600;

   int i =0;


   //Creating some first test map

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
void GameData::insertitems (int const& index, int const & mapWidth, int const& mapHeight, int size)
{


}

void GameData::loadmap()
{
        QString fileName = QFileDialog::getOpenFileName(this, "Open the file");
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly | QFile::Text)) {
            QMessageBox::warning(this,"..","File not opened.");
            return;
        }
        QTextStream in(&file);
        QString text = in.readAll(); // whole file is saved as one row with \n symbols
        file.close();

        int mapHeight, mapWidth, itemPositionX, itemPositionY;
        int index = text.indexOf("\n",0);
        QString map = text.left(index);
        index += 1; // moving index to next row. First row purpose is to select bacground

        mapWidth = text.indexOf("\n",index);
        mapHeight = text.count("\n");

        QString path = ":/images/";
                path.append("background2.bmp");
        QImage picture(path);
        background = new movingItem();
        background->setPixmap(QPixmap::fromImage(picture));

        insertitems(index,mapWidth,mapHeight, text.length()); // looking for symbols # , $ which represents objects on the map ( there will be more in the future)


        qDebug() << mapWidth <<" "<< mapHeight <<" 8%5=" << 8%5;



}





} // namespace game
