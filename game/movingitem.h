#ifndef MOVINGITEM_H
#define MOVINGITEM_H

#include "game/mapitem.h"

namespace game{

class movingItem : public mapItem
{
public:
    movingItem();
    movingItem(int speedx,
               int speedy,
               int posx,
               int posy);
    void accelerate(int accelerate_value);
    void jump();
    void move();

private:
    int speedX;
    int speedY;
};

} // namespcae game

#endif // MOVINGITEM_H
