#ifndef MOVINGITEM_H
#define MOVINGITEM_H

#include "game/mapitem.h"

namespace game{

enum user_action {
        MOVE_LEFT,
        MOVE_RIGHT,
        JUMP,
        SHOOT,
        IDLE
};

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
    void setAction(user_action a);
    void releaseAction(user_action a);


//private: (make it public) TODO checking collisions changes speed, handle it nicer (in function)
    int speedX;
    int speedY;
    std::vector<user_action*> actions;

};

} // namespcae game

#endif // MOVINGITEM_H
