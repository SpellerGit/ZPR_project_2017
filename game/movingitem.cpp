#include "movingitem.h"
#include <QDebug>

namespace game {

movingItem::movingItem()
{
    speedX =0;
    speedY =0;
}

movingItem::movingItem(int speedx,
                       int speedy,
                       int posx,
                       int posy)
    : speedX(speedx), speedY(speedy) //random formating,sry...
{
    posX = posx;
    posY = posy;
}

void movingItem::accelerate(int accelerate_value)
{
    speedX+=accelerate_value;
}

void movingItem::jump()
{
    speedY=-10; //50 temporary value
}

void movingItem:: move()
{
  //  qDebug() <<"speed x is " << speedX;
  //  qDebug() <<"speed y is " << speedY;

    posX=posX+speedX;
    posY=posY+speedY;

    if(speedX!=0)
    {
        if(speedX<0)
        speedX=speedX+1;

        if(speedX>0)
        speedX=speedX-1;
    }
    //if(speedY!=0)
        speedY=speedY+2; // here, when we can detect collisions we should gain speed down
                          //until we reach ground (collision is detected)
}

} // namespace game
