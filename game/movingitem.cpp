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
    : speedX(speedx), speedY(speedy)
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
    speedY=-16; // temporary value
}

void movingItem:: move()
{
    posX=posX+speedX;
    posY=posY+speedY;

    if(speedX!=0)
    {
        if(speedX<0)
        speedX=speedX+5;

        if(speedX>0)
        speedX=speedX-5;
    }
    if(speedY<40) //40 - temp value, max velocity
        speedY=speedY+4;
}

} // namespace game
