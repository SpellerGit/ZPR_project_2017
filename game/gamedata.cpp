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
   auto player = new movingItem(0,0,200,250);
   player->setPixmap(QPixmap::fromImage(image));
   player->hitPoints=100;

   players.push_back(player);

   auto player2 = new movingItem(0,0,200,200,100); //aka the cpu player
   player2->setPixmap(QPixmap::fromImage(image));

   players.push_back(player2);



   QImage image3(":/images/tile1.bmp");

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

       i+=50;
       if(i>1000)
           break;
   }

   bullets = std::vector<movingItem*>();

}


void GameData::loadmap(){

    // Destroying previous map set
       players.clear();
       tiles.clear();
       bullets.clear();

    // Opening map file, getting map height, objects to add etc.
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


       mapWidth = text.indexOf("\n",index); /// map withd is countig from 0
       mapWidth= mapWidth - index; // we get true width of the map
       qDebug() << mapWidth;
       mapHeight = text.count("\n");
       qDebug() << mapHeight;

       text.remove("\n");
       text.remove(map);

       qDebug() << text; // will use that later -> to add new tiles to the map


       QString path = ":/images/";
               path.append(map);

               background.replace(0,100,path);
               qDebug() << background;

       QImage picture(path);


       // Here we can modify or add new tiles type
       // # - regular tile , % - nothing for now, X - player position soon

       char element [] = {'#' , 'X', };

                                QImage standardTile(":/images/tile1.bmp");         // tile image -> #
                                QImage playerImage(":/images/image3.png");     // player image ->X


                                auto player = new movingItem(0,0,200,250);    // Setting possition of first player
                                player->setPixmap(QPixmap::fromImage(playerImage));
                                player->hitPoints=100;

                                players.push_back(player);

                                auto player2 = new movingItem(0,0,200,200,100); //aka the cpu player
                                player2->setPixmap(QPixmap::fromImage(playerImage));

                                players.push_back(player2); // for testing



       for(int i = 0; i < sizeof(element); i++)
       {
               int possition = 0;
               int zmienna = 0;

               switch( element[i] )
               {
                   case '#':
                       for(int j=0; j<text.size();j++) // size of map
                       {
                           int Scale = 50;
                         //  qDebug() << "possition " << j << ": " << possition << " and text.size : " << text.size() ;



                           possition = text.indexOf("#",possition) ; // same as before , we are getting true possition of map
                           if(possition == -1)
                           {qDebug() <<"no more tiles!";
                               break;
                           }
                           zmienna = possition;

                           qDebug() << " possition issues : " << zmienna<< " and index: "<< index;

                          int Xpossition =(zmienna) % mapWidth;
                          int Ypossition =((zmienna) + (mapWidth - Xpossition))/mapWidth;  // getting possition of tiles. must scale to poin 0,0 so i use "- index" which contanins size of first line

                           qDebug() << "new tile in collection pos X, Y : " << Xpossition << ", "<< Ypossition;
                           mapItem * tile = new movingItem();
                           tile->setPixmap(QPixmap::fromImage(standardTile)); // posX is starting from 0 , so i will decrease Xpossition and Ypossition
                           tile->posX= (Xpossition ) * Scale;
                           tile->posY= (Ypossition ) * Scale;
                           tiles.push_back(tile);

                           possition = possition + 1;

                       }
                       break;

                   case 'X':   // Other players possition.
                        for(int j=0; j<text.size();j++)
                        {

                           break;
                         }
                        break;

                   default:
                       break;
                      //
               }
       }
}





movingItem* GameData::addBullet(int shootPointX,
                                int shootPointY,
                                int playerNumer)
                                          //first prototype version, must get much more customizable in future
                                          //Also cleaner
{
    //We want to bullet appear on screen in right place, next to player and towards shooting direction
    QPoint middle(players[playerNumer]->x()+players[playerNumer]->boundingRect().width()/2,
                  players[playerNumer]->y()+players[playerNumer]->boundingRect().height()/2);

    const int fullSpeed = 100; //tmp

    int tempx=1;
    int tempy=1;

    if(shootPointX-middle.x()<0)
        tempx=-1;

    if(shootPointY-middle.y()<0)
        tempy=-1;

    float diffX = abs(shootPointX-middle.x());
    float diffY = abs(shootPointY-middle.y()); //can user break the game when he presses on himself?
                                                 //we would get zero division maybe we should handle this error

    float ratio = diffX/(diffX+diffY); //i am doing this to get angle at which the bullet is shot

    float speedx = ratio*fullSpeed * tempx;
    float speedy = (1-ratio)*fullSpeed * tempy;

    movingItem * bullet = new movingItem((int)speedx,(int)speedy,middle.x(),middle.y(),10); //setting hp to tmp 10

    QImage image(":/images/bullet.png");
    bullet->setPixmap(QPixmap::fromImage(image));

    if(abs(speedx)>abs(speedy))
    {
        float ratio2 = players[playerNumer]->boundingRect().width()/abs(speedx);
        bullet->setPos(middle.x()+speedx*ratio2,middle.y()+speedy*ratio2);
    }
    else
    {
        float ratio2 = players[playerNumer]->boundingRect().height()/abs(speedy);
        bullet->setPos(middle.x()+speedx*ratio2,middle.y()+speedy*ratio2);
    }

    return bullet;

}

} // namespace game
