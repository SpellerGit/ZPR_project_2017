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
    movingItem(int speedx,
               int speedy,
               int posx,
               int posy,
               int hp);
    void accelerate(int accelerate_value);
    void jump();
    void move();
    bool destroyed();

//private: (make it public) TODO checking collisions changes speed, handle it nicer (in function)
    int speedX;
    int speedY;
};

} // namespcae game

#endif // MOVINGITEM_H
